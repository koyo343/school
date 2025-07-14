% ��B�H�Ƒ�w���H�w�����E�ʐM�H�w��3�N
% ��񗝘_ ���K�ۑ�1 ���K3
% 2024/05/10 ���萳�s

clear;                                 
clearvars -global;                    
close all;                            
clc;                                   
%% Parameter setting
StudentID = 029;             % �w�Дԍ��̉��R���ɕύX���邱��
seed = StudentID;           % �w�Дԍ��𗐐��̃V�[�h�l�ɐݒ�
rng(seed);                        % �����̃V�[�h�l�̐ݒ�

CurrentState = 1;            % ���݂̏�� (�������1)
NextState = 1;                % ���̏�� 

NIteration = 10;             % �J�Ԃ���

StateHist = zeros(1, NIteration);

%% Start simulation
for ite = 1: NIteration

    Transition = rand;                                                    % �����_���l�̐���
    StateHist(ite) = CurrentState;                                  % ���݂̏�Ԃ̔ԍ����i�[

    switch CurrentState
        case 1                                                                  % ���1�ɂ����铮����L�q
            if Transition < 0.3                                            % 0.3�̊m���ŏ��1�ɑJ��
                NextState = 1;
            elseif Transition >= 0.3 && Transition < 0.6   % 0.6-0.3=0.3�̊m���ŏ��1�ɑJ��
                NextState = 2;
            else                                                                  % 0.4�̊m���ŏ��3�ɑJ��
                NextState = 3;
            end
        case 2                                                                  % ���2�ɂ����铮����L�q
            if Transition < 0.3                                            % 0.3�̊m���ŏ��1�ɑJ��
                NextState = 1;
            elseif Transition >= 0.3 && Transition < 0.6   % 0.3�m���ŏ��2�ɑJ��
                NextState = 2;
            else                                                                  % 0.4�̊m���ŏ��2�ɑJ��
                NextState = 3;
            end
        case 3                                                                  % ���3�ɂ����铮����L�q
            if Transition < 0.3                                            % 0.3�̊m���ŏ��1�ɑJ��
                NextState = 1;
            elseif Transition >= 0.3 && Transition < 0.6   % 0.3�̊m���ŏ��2�ɑJ��
                NextState = 2;
            else                                                                  % 0.4�̊m���ŏ��2�ɑJ��
                NextState = 3;
            end
        otherwise
            NextState=1;
    end
    CurrentState = NextState;
end

%% Evaluation
% �ŏ�����10��̑J�ڂ�\��
disp('State History');
disp(StateHist(1:10));

% �q�X�g�O�����̃O���t�̕\��
h = histogram(StateHist);

% �p�x�̕\��
%
 disp('State Frequency');
 disp('State   Count   Percent');
 fprintf('   S1, %6d, %8.3f %%\n', h.Values(1),h.Values(1)/NIteration*100);
 fprintf('   S2, %6d, %8.3f %%\n', h.Values(2),h.Values(2)/NIteration*100);
 fprintf('   S3, %6d, %8.3f %%\n', h.Values(3),h.Values(3)/NIteration*100);
