module DecToBinary (
    input  wire [3:0] dec_in,
    output reg  [3:0] bin_out
);

    always @(*) begin
        case (dec_in)
            4'd0:    bin_out = 4'b0000;
            4'd1:    bin_out = 4'b0001;
            4'd2:    bin_out = 4'b0010;
            4'd3:    bin_out = 4'b0011;
            4'd4:    bin_out = 4'b0100;
            4'd5:    bin_out = 4'b0101;
            4'd6:    bin_out = 4'b0110;
            4'd7:    bin_out = 4'b0111;
            4'd8:    bin_out = 4'b1000;
            4'd9:    bin_out = 4'b1001;
            default: bin_out = 4'bxxxx; //それ以外の入力は不定値Xを出力
        endcase
    end

endmodule