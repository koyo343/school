#include <kilolib.h>

message_t send_msg;   // 送信メッセージ格納用
uint8_t sent_message;   // 送信の確認用変数
uint8_t recved_message;   // 受信の確認用変数
message_t recv_msg;   // 受信メッセージ格納用
uint8_t dis;   // 受信時の距離格納用

// 送信メッセージのアドレスを渡すコールバック
message_t *tx_message(){
    return &send_msg;
}
// 送信成功のたびに実行される
void tx_message_success(){
    sent_message = 1;
}
// 受信成功のたびに実行される
void rx_message(message_t *msg, distance_measurement_t *d){
    recv_msg = msg;
    dis = estimate_disrance(const distance_measurement_t *d);
    if (dis<=70) {
        recved_message = 1;
    }
}

// 他のロボットのデータ格納用
// [0]:id,[1]:最新のdis,[2]:前回のdis,[3]最終更新時間
uint8_t robo_data[9][4] = {0};
uint8_t robo_id;   // ロボットのid、乱数で設定
int8_t dir = 0;   // 進行方向を表す変数(dir<0:左回り、0<=dir:右回り)
int8_t dir1 = 0;
int8_t dir2 = 0;
uint8_t border = 40;   //   ロボットの集合と分離の境界(半径40mm)
uint8_t others = 0;   // 通信した他のロボットの数
uint8_t new_robo = 1;   // 受信が初めてかの管理用変数
unsigned int set_time = 0;   // direction更新のための時間格納用変数
uint8_t wait_time = 32;   // direction更新の時間間隔(32ごとに1秒)
uint8_t min1_dis = 255;   // 一番目に小さいdistanceを格納
uint8_t min2_dis = 255;   // 二番目
uint8_t min1_num = 255;   // min1_disを持つロボットの番号(idではない)
uint8_t min2_num = 255;   // robo_data[i][j]のi
uint8_t base = 50;
uint8_t motor_base = 50;
uint8_t motor_left = 0;
uint8_t motor_right = 0;
uint8_t ratio = 0.5;
uint8_t i = 0;
uint8_t clr = 0;



void setup() {
    // 記録用配列の初期化
    for(i=0;i<9;i++) {
        robo_data[i][0] = -1;
        robo_data[i][1] = 40;
        robo_data[i][2] = 40;
    }
    // ロボットのidの設定
    rand_seed(rand_hard());
    robo_id = rand_soft();
    // 送信メッセージの設定
    send_msg.data[0] = robo_id;
    for (i=1;i<=8;i++) {
        send_msg.data[i] = 0;
    }
    send_msg.type = NORMAL;
    send_msg.crc = message_crc(&send_msg);
    // direction更新のため時間格納
    set_time = kilo_ticks;
    // 直進開始
    set_motors(motor_base,motor_base);
}

// 前回のdir,今回と前回のdisから次のdisを決定
uint8_t direction(uint8_t min_num) {
    uint8_t dir_r;
    uint8_t dis_1 = robo_data[min_num][1];
    uint8_t dis_2 = robo_data[min_num][2];
    if (dir>=0) {
        if (dis_1>=border) {
            if (dis_1>dis_2) {
                dir_r = (dis_1-border)*(-1);
            }
            else if (dir1<=dis_2) {
                dir_r = (dis_1-border);
            }
        }
        else if (dis_1<border) {
            if (dis_1>=dis_2) {
                dir_r = (dis_1-border);
            }
            else if (dir1<dis_2) {
                dir_r = (dis_1-border)*(-1);
            }
        }
    }
    else if (dir<0) {
        if (dis_1>=border) {
            if (dis_1>dis_2) {
                dir_r = (dis_1-border);
            }
            else if (dir1<=dis_2) {
                dir_r = (dis_1-border)*(-1);
            }
        }
        else if (dis_1<border) {
            if (dis_1>=dis_2) {
                dir_r = (dis_1-border)*(-1);
            }
            else if (dir1<dis_2) {
                dir_r = (dis_1-border);
            }
        }
    }
    return dir_r;
}

// 進行方向設定
void set_dir() {
    dir1 = 0;
    dir2 = 0;
    min1_dis = 255;
    min1_num = 255;
    min2_dis = 255;
    min2_num = 255;
    // 最も近いロボットを探す
    for (i=0;i<others;i++) {
        // 前回の更新以降に通信したロボットのみを対象にする
        if ((kilo_ticks-robo_data[i][3])<=wait_time) {
            if (min1_dis>=robo_data[i][1]) {
                min2_dis = min1_dis;
                min2_num = min1_num;
                min1_dis = robo_data[i][1];
                min1_num = i;
            }
            else if (min2_dis>=robo_data[i][1]) {
                min2_dis =robo_data[i][1];
                min2_num = i;
            }
        }
    }
    // 一番目と二番目に近いロボットの距離からdirを計算
    if (min1_num!=255) {
        dir1 = direction(min1_num);
        if (min2_num!=255) {
            dir2 = direction(min2_num)/2;
        }
    }
    dir = dir1+dir2;


    if (dir>0) {
        motor_base = base+dir;
    }
    else if (dir<0) {
        motor_base = base-dir;
    }
    motor_right = motor_base-(dir*ratio);
    motor_left = motor_base+(dir*ratio);
    // 前回のdisを更新
    for (i=0;i<others;i++) {
        robo_data[i][2] = robo_data[i][1];
    }
}

void loop() {
    // 受信メッセージ格納
    if (recved_message) {
        recved_message = 0;
        new_robo = 1;
        // 通信したことのあるロボットか探索する
        for (i=0;i<others;i++) {
            if (recv_msg.data[0]==robo_data[i][0]) {
                // 受信時のdistanceを記録
                robo_data[i][1] = dis;
                // 受信した時間を記録、kilo_ticksの戻り値は一秒ごとに32ずつ増える
                robo_data[i][3] = kilo_ticks;
                new_robo = 0;
                break;
            }
        }
        // 新しく通信したロボットidを追加
        if (new_robo==1) {
            robo_data[others][0] = recv_msg.data[0];
            robo_data[others][1] = dis.high_gain-dis.low_gain;
            robo_data[others][3] = kilo_ticks;
            others = others+1;
        }
    }
    if ((kilo_ticks-set_time)>=wait_time) {
        set_dir();
        set_time = kilo_ticks;
        set_motors(motor_left,motor_right);
        if (clr == 1){
            set_color(RGB(1,0,0));
            clr = 0;
        }
        else if (clr == 0){
            set_color(RGB(0,1,0));
            clr = 1;
        }
    }
}

int main() {
    // ハードウェア更新
    kilo_init();

    // 送信メッセージのアドレスを設定
    kilo_message_tx = tx_message;
    // 送信成功の度に設定した関数を実行
    kilo_message_tx_success = tx_message_success;

    // 受信メッセージを格納するポインタを設定
    kilo_message_rx = rx_message;

    // プログラムスタート、setupを一度だけ実行後loopを繰り返す
    kilo_start(setup, loop);

    return 0;
}