module top (a, b, cin, sum, cout);
    input   [3:0]   a;
    input   [3:0]   b;
    input           cin;
    output  [3:0]   sum;
    output          cout;
    add4_head add4_1(.a(a),.b(b),.cin(cin),.sum(sum));
    /* add4 add4_1(.a(a),.b(b),.cin(cin),.sum(sum),.cout(cout)); */
endmodule



module add4_head (a, b, cin, sum);
    input   [3:0]   a;
    input   [3:0]   b;
    input           cin;
    output  [3:0]   sum;
    wire c1, c2, c3;
    assign c1   = (a[0] & b[0]) | ((a[0] + b[0]) & cin);
    assign c2   = (a[1] & b[1]) | ((a[1] + b[1]) & c1);
    assign c3   = (a[2] & b[2]) | ((a[2] + b[2]) & c2);
    assign sum  = {a[3] ^ b[3] ^ c3, a[2] ^ b[2] ^ c2, a[1] ^ b[1] ^ c1, a[0] ^ b[0] ^ cin};
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
