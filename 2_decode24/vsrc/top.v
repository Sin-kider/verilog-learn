module top (x, en, y);
    input [1:0]x;
    input en;
    output reg [3:0]y;
    always @(*) begin
        if (en) begin
            case (x)
                2'h0: y = 4'b0001;
                2'h1: y = 4'b0010;
                2'h2: y = 4'b0100;
                2'h3: y = 4'b1000;
                default: y = 4'b0000;
            endcase
        end
        else begin
            y = 4'b000;
        end
    end
endmodule
