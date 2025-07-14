% 九州工業大学情報工学部情報・通信工学科3年
% 情報理論 演習課題1 演習3
% 2024/05/10 黒崎正行

clear;                                 
clearvars -global;                    
close all;                            
clc;                                   
%% Parameter setting
StudentID = 029;             % 学籍番号の下３桁に変更すること
seed = StudentID;           % 学籍番号を乱数のシード値に設定
rng(seed);                        % 乱数のシード値の設定

CurrentState = 1;            % 現在の状態 (初期状態1)
NextState = 1;                % 次の状態 

NIteration = 10;             % 繰返し回数

StateHist = zeros(1, NIteration);

%% Start simulation
for ite = 1: NIteration

    Transition = rand;                                                    % ランダム値の生成
    StateHist(ite) = CurrentState;                                  % 現在の状態の番号を格納

    switch CurrentState
        case 1                                                                  % 状態1における動作を記述
            if Transition < 0.3                                            % 0.3の確率で状態1に遷移
                NextState = 1;
            elseif Transition >= 0.3 && Transition < 0.6   % 0.6-0.3=0.3の確率で状態1に遷移
                NextState = 2;
            else                                                                  % 0.4の確率で状態3に遷移
                NextState = 3;
            end
        case 2                                                                  % 状態2における動作を記述
            if Transition < 0.3                                            % 0.3の確率で状態1に遷移
                NextState = 1;
            elseif Transition >= 0.3 && Transition < 0.6   % 0.3確率で状態2に遷移
                NextState = 2;
            else                                                                  % 0.4の確率で状態2に遷移
                NextState = 3;
            end
        case 3                                                                  % 状態3における動作を記述
            if Transition < 0.3                                            % 0.3の確率で状態1に遷移
                NextState = 1;
            elseif Transition >= 0.3 && Transition < 0.6   % 0.3の確率で状態2に遷移
                NextState = 2;
            else                                                                  % 0.4の確率で状態2に遷移
                NextState = 3;
            end
        otherwise
            NextState=1;
    end
    CurrentState = NextState;
end

%% Evaluation
% 最初から10回の遷移を表示
disp('State History');
disp(StateHist(1:10));

% ヒストグラムのグラフの表示
h = histogram(StateHist);

% 頻度の表示
%
 disp('State Frequency');
 disp('State   Count   Percent');
 fprintf('   S1, %6d, %8.3f %%\n', h.Values(1),h.Values(1)/NIteration*100);
 fprintf('   S2, %6d, %8.3f %%\n', h.Values(2),h.Values(2)/NIteration*100);
 fprintf('   S3, %6d, %8.3f %%\n', h.Values(3),h.Values(3)/NIteration*100);
