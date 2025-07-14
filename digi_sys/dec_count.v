module DecimalCounter (
    input  wire       CK,
    input  wire       RES,
    output reg  [3:0] count
);

    always @(posedge CK or posedge RES) begin
        if (RES)
            count <= 4'd0;
        else if (count == 4'd9)
            count <= 4'd0;
        else 
            count <= count + 1;
    end

endmodule