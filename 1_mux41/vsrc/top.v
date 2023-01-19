module top (a, s, y);
    input [3:0]a;
    input [1:0]s;
    output reg y;
    always @(*) begin
        case (s)
            2'h0: y = a[0];
            2'h1: y = a[1];
            2'h2: y = a[2];
            2'h3: y = a[3];
            default: y = 0'b0;
        endcase
    end
endmodule
