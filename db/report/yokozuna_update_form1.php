<HTML>
<HEAD>
  <TITLE>横綱の更新フォーム（動的生成版）</TITLE>
  <META http-equiv="Content-Type" content="text/html; charset=UTF-8">
</HEAD>
<BODY>

<CENTER>

横綱データ 更新フォーム<BR><BR>

更新したい横綱を選択して送信ボタンを押してください。<BR><BR>

<FORM ACTION="yokozuna_update_form2.php" METHOD="GET">

<!-- ここからPHPのスクリプト始まり -->
<?php

// データベースに接続
// ※ your_db_name のところは自分のデータベース名に書き換える
$conn = pg_connect( "dbname=agdo2465" );

// 接続が成功したかどうか確認
if ( $conn == null )
{
    print( "データベース接続処理でエラーが発生しました。<BR>" );
    exit;
}

// SQLを作成
$sql = "select id, yokozuna.name, room.name, fro, promo_year  from yokozuna, room where yokozuna.room_no = room.room_no order by id";

// Queryを実行して検索結果をresultに格納
$result = pg_query( $conn, $sql );
if ( $result == null )
{
    print( "クエリー実行処理でエラーが発生しました。<BR>" );
    exit;
}

// 検索結果の行数・列数を取得
$rows = pg_num_rows( $result );
$cols = pg_num_fields( $result );


// 検索結果をテーブルとして表示
print( "<TABLE BORDER=1>\n" );

// 各列の名前を表示
print( "<TR>" );
print( "<TH>横綱代数</TH>" );
print( "<TH>部屋</TH>" );
print( "<TH>四股名</TH>" );
print( "<TH>出身</TH>" );
print( "<TH>横綱昇進日</TH>" );
print( "</TR>\n" );

// 各行のデータを表示
for ( $j=0; $j<$rows; $j++ )
{
    print( "<TR>" );
    
// 横綱番号と選択のためのラジオボタンを表示
    $data = pg_fetch_result( $result, $j, 0 );
    print( "<TD> <INPUT TYPE=\"radio\" NAME=\"id\" VALUE=\"$data\"> $data </INPUT> </TD>\n" );
    
    // 残りの属性値を表示（$iが1から始まっている点に注意）
    for ( $i=1; $i<$cols; $i++ )
    {
        // j行i列のデータを取得
        $data = pg_fetch_result( $result, $j, $i );
        
        // セルに列の名前を表示
        print( "<TD> $data </TD>" );
    }
    
    print( "</TR>\n" );
}

// ここまででテーブル終了
print( "</TABLE>" );
print( "<BR>\n" );


// 検索件数を表示
print( "以上、$rows 人の横綱が登録されています。<BR>\n" );


// 検索結果の開放
pg_free_result( $result );

// データベースへの接続を解除
pg_close( $conn );

?>
<!-- ここまででPHPのスクリプト終わり -->

<BR>
<INPUT TYPE="submit" VALUE="送信"><BR>

</FORM>

<BR>
<A HREF="rep_menu.html">操作メニューに戻る</A>

</CENTER>

</BODY>
</HTML>