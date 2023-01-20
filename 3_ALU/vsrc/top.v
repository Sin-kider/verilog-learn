module top (x, en, y);
    input [3:0]x;
    input en;
    output reg [1:0]y;
    integer i;
    always @(*) begin
        if (en) begin
            y = 2'b00;
            for (i = 0; i < 4; i++) begin
                if (x[i] == 1) begin
                    y = i[1:0];
                end
            end
        end
        else begin
            y = 2'b00;
        end
    end
endmodule



module add4 (a, b, cin, sum, cout);
    input   [3:0]   a;
    input   [3:0]   b;
    input           cin;
    output  [3:0]   sum;
    output          cout;
    wire c1, c2, c3;
    assign c1   = (a[0] & b[0]) | ((a[0] + b[0]) & cin);
    assign c2   = (a[1] & b[1]) | ((a[1] + b[1]) & c1);
    assign c3   = (a[2] & b[2]) | ((a[2] + b[2]) & c2);
    assign cout = (a[3] & b[3]) | ((a[3] + b[3]) & c3);
    assign sum  = {a[3] ^ b[3] ^ c3, a[2] ^ b[2] ^ c2, a[1] ^ b[1] ^ c1, a[0] ^ b[0] ^ cin};
endmodule
