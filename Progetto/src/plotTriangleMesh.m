nodes = [0,0;
1,0;
1,1;
0,1;
0.5,0.5;
0,0.5;
0.0625,0.625;
0.25,0.5;
0,0.25;
0.5,0;
0,0.75;
0.125,0.5;
0.5,1;
0.433275,0.815849;
0.148437,0.746094;
0.195626,0.621564;
0.529625,0.683244;
0.375,0.628853;
0.25,1;
0.373136,0.732013;
0.286769,0.589388;
0.375,0.500839;
0.27482,0.700717;
0.313771,0.311229;
0.313066,0.416148;
0.0625,0.375;
0.193152,0.362881;
0.25,0;
0.221019,0.261294;
0.110735,0.251224;
0.0567566,0.125;
0.289186,0.855722;
0.0775596,0.875;
0.232942,0.782767;
0.125,1;
0.186981,0.904974;
0.344656,0.142753;
0.125,0;
0.472573,0.598451;
0.924569,0.625;
0.38898,0.936063;
0.211891,0.128028;
0.375,0;
0.547402,0.26699;
0.444875,0.364572;
0.417838,0.243238;
0.47281,0.126311;
0.625,0;
0.75,0;
0.536065,0.78923;
0.75,1;
1,0.5;
0.6875,0.0694813;
0.585002,0.116209;
0.625,1;
0.642467,0.570984;
0.508074,0.892911;
1,0.25;
0.668679,0.727983;
0.749387,0.852019;
0.628269,0.869741;
0.736262,0.636012;
0.802373,0.440498;
0.82784,0.586474;
0.741191,0.528744;
0.632806,0.411914;
0.615033,0.656252;
0.854872,0.752318;
0.534065,0.407201;
1,0.75;
0.875,0.925491;
0.897806,0.481478;
1,0.375;
0.591791,0.494234;
0.722482,0.261441;
0.67209,0.171457;
0.774275,0.134747;
1,0.875;
0.839631,0.841845;
0.759557,0.757126;
0.92931,0.8125;
0.869619,0.3125;
0.875,0.0470411;
0.911511,0.392352;
0.775933,0.344943;
0.817138,0.226203;
1,0.125;
0.915154,0.1875;
0.63646,0.312134;
];
triangles = [76,77,75;
12,6,26;
8,16,12;
11,6,7;
24,45,25;
25,22,8;
24,27,29;
12,7,6;
6,9,26;
28,42,38;
14,17,50;
7,15,11;
17,20,18;
21,16,8;
25,45,22;
16,23,15;
34,15,23;
16,15,7;
15,33,11;
50,57,14;
12,16,7;
18,21,22;
35,36,19;
4,11,33;
14,20,17;
14,32,20;
23,18,20;
17,18,39;
41,57,13;
59,50,17;
22,21,8;
32,14,41;
12,27,8;
22,5,39;
16,21,23;
18,23,21;
24,25,27;
37,29,42;
12,26,27;
46,24,37;
9,1,31;
8,27,25;
26,9,30;
29,37,24;
42,30,31;
27,26,30;
42,28,37;
9,31,30;
30,29,27;
10,47,43;
24,46,45;
15,34,36;
20,32,34;
35,4,33;
20,34,23;
34,32,36;
36,33,15;
36,35,33;
19,36,32;
47,46,37;
22,39,18;
31,1,38;
39,5,74;
89,85,66;
13,57,55;
13,19,41;
19,32,41;
30,42,29;
38,42,31;
48,49,53;
37,28,43;
68,64,40;
44,89,69;
22,45,5;
37,43,47;
44,45,46;
44,47,54;
44,46,47;
48,53,54;
39,56,67;
59,17,67;
10,48,54;
71,51,60;
55,57,61;
41,14,57;
84,52,72;
57,50,61;
2,83,49;
64,65,63;
54,47,10;
60,61,59;
67,62,59;
59,61,50;
62,64,68;
63,85,82;
74,65,56;
54,53,76;
68,80,62;
61,51,55;
68,40,70;
61,60,51;
65,62,56;
71,3,51;
65,66,63;
73,82,58;
70,40,52;
72,40,64;
39,74,56;
63,72,64;
45,69,5;
69,89,66;
39,67,17;
62,67,56;
70,78,81;
80,79,60;
44,69,45;
74,69,66;
40,72,52;
65,64,62;
78,3,71;
79,80,68;
82,86,88;
79,71,60;
77,86,75;
84,82,73;
69,74,5;
65,74,66;
44,54,76;
84,63,82;
77,76,53;
76,75,89;
49,77,53;
83,87,88;
68,70,81;
71,79,81;
60,59,80;
62,80,59;
71,81,78;
68,81,79;
88,87,58;
77,49,83;
52,84,73;
63,84,72;
66,85,63;
86,85,75;
77,83,88;
85,86,82;
82,88,58;
83,2,87;
88,86,77;
76,89,44;
85,89,75;
];
figure;trimesh(triangles, nodes(:,1), nodes(:,2));
nodes = [0,0;
1,0;
1,1;
0,1;
0.5,0.5;
0,0.5;
0.0625,0.625;
0.25,0.5;
0,0.25;
0.5,0;
0,0.75;
0.125,0.5;
0.5,1;
0.433275,0.815849;
0.148437,0.746094;
0.195626,0.621564;
0.529625,0.683244;
0.375,0.628853;
0.25,1;
0.373136,0.732013;
0.286769,0.589388;
0.375,0.500839;
0.27482,0.700717;
0.313771,0.311229;
0.313066,0.416148;
0.0625,0.375;
0.193152,0.362881;
0.25,0;
0.221019,0.261294;
0.110735,0.251224;
0.0567566,0.125;
0.289186,0.855722;
0.0775596,0.875;
0.232942,0.782767;
0.125,1;
0.186981,0.904974;
0.344656,0.142753;
0.125,0;
0.472573,0.598451;
0.924569,0.625;
0.38898,0.936063;
0.211891,0.128028;
0.375,0;
0.547402,0.26699;
0.444875,0.364572;
0.417838,0.243238;
0.47281,0.126311;
0.625,0;
0.75,0;
0.536065,0.78923;
0.75,1;
1,0.5;
0.6875,0.0694813;
0.585002,0.116209;
0.625,1;
0.642467,0.570984;
0.508074,0.892911;
1,0.25;
0.668679,0.727983;
0.749387,0.852019;
0.628269,0.869741;
0.736262,0.636012;
0.802373,0.440498;
0.82784,0.586474;
0.741191,0.528744;
0.632806,0.411914;
0.615033,0.656252;
0.854872,0.752318;
0.534065,0.407201;
1,0.75;
0.875,0.925491;
0.897806,0.481478;
1,0.375;
0.591791,0.494234;
0.722482,0.261441;
0.67209,0.171457;
0.774275,0.134747;
1,0.875;
0.839631,0.841845;
0.759557,0.757126;
0.92931,0.8125;
0.869619,0.3125;
0.875,0.0470411;
0.911511,0.392352;
0.775933,0.344943;
0.817138,0.226203;
1,0.125;
0.915154,0.1875;
0.63646,0.312134;
0.748378,0.198094;
0.723182,0.153102;
0.160313,0.560782;
0,0.625;
0.379323,0.337901;
0,0.375;
0.03125,0.3125;
0.105469,0.685547;
0.452312,0.656049;
0.211629,0.723405;
0,0.875;
0.361231,0.835786;
0.159076,0.431441;
0.423787,0.549645;
0.375,0.564846;
0.330884,0.545114;
0.282837,0.202024;
0,0.125;
0.0283783,0.1875;
0.161313,0.189626;
0.134324,0.126514;
0.168445,0.0640138;
0.151944,0.307053;
0.297328,0.0713766;
0.423905,0.0631556;
0.167709,0.825534;
0.0908783,0.0625;
0.375,1;
0.841356,0.669396;
0.55752,0.584718;
0.542501,0.0581045;
0.605001,0.0581045;
0.636251,0.0928451;
0.815107,0.513486;
0.709033,0.790001;
0.648474,0.798862;
0.582167,0.829485;
0.675647,0.646132;
0.795567,0.694165;
0.835996,0.376499;
0.747909,0.696569;
0.875,1;
0.9375,0.962745;
0.71759,0.426206;
0.70437,0.378429;
0.686999,0.470329;
0.666491,0.511489;
0.93481,0.34375;
0.93481,0.28125;
1,0.625;
0.962285,0.6875;
0.927436,0.751159;
0.892387,0.25;
0.762137,0.0673734;
0.9375,0.0860206;
0.892091,0.782409;
1,0.1875;
0.796535,0.285573;
0.844714,0.161123;
];
triangles = [77,75,76;
12,6,26;
16,12,8;
11,6,7;
24,45,25;
25,22,8;
24,27,29;
12,7,6;
6,9,26;
42,38,28;
14,17,50;
7,15,11;
18,17,20;
21,16,8;
25,45,22;
23,15,16;
15,23,34;
15,7,16;
15,33,11;
50,57,14;
12,16,7;
22,18,21;
35,36,19;
4,11,33;
14,20,17;
14,32,20;
23,18,20;
17,18,39;
41,57,13;
59,50,17;
22,21,8;
32,14,41;
12,27,8;
39,22,5;
16,21,23;
18,23,21;
24,25,27;
37,29,42;
27,12,26;
46,24,37;
9,1,31;
8,27,25;
26,9,30;
29,37,24;
42,30,31;
30,27,26;
28,37,42;
9,31,30;
27,30,29;
47,43,10;
45,24,46;
36,15,34;
20,32,34;
35,4,33;
20,34,23;
34,32,36;
15,36,33;
36,35,33;
19,36,32;
47,46,37;
22,39,18;
38,31,1;
39,5,74;
85,66,89;
13,57,55;
13,19,41;
19,32,41;
30,42,29;
42,31,38;
48,49,53;
37,28,43;
68,64,40;
44,89,69;
22,45,5;
43,47,37;
44,45,46;
44,47,54;
44,46,47;
54,48,53;
39,56,67;
59,17,67;
54,10,48;
71,51,60;
55,57,61;
41,14,57;
84,52,72;
50,61,57;
2,83,49;
63,64,65;
10,54,47;
59,60,61;
67,62,59;
59,61,50;
64,68,62;
82,63,85;
74,65,56;
54,53,76;
62,68,80;
61,51,55;
40,70,68;
61,60,51;
65,62,56;
3,51,71;
66,63,65;
73,82,58;
52,70,40;
72,40,64;
56,39,74;
64,63,72;
45,69,5;
69,89,66;
39,67,17;
62,67,56;
70,78,81;
80,79,60;
44,69,45;
74,69,66;
40,72,52;
65,64,62;
3,71,78;
79,80,68;
88,82,86;
79,71,60;
75,77,86;
82,73,84;
69,74,5;
66,65,74;
44,54,76;
63,82,84;
77,76,53;
76,75,89;
49,77,53;
83,87,88;
68,70,81;
71,79,81;
60,59,80;
62,80,59;
71,81,78;
68,81,79;
87,58,88;
77,49,83;
52,84,73;
63,84,72;
63,66,85;
86,85,75;
88,77,83;
85,86,82;
58,82,88;
87,83,2;
77,88,86;
76,89,44;
85,89,75;
75,90,86;
90,77,86;
75,76,90;
76,77,90;
77,91,53;
91,76,53;
77,90,91;
91,90,76;
12,92,7;
92,16,7;
12,8,92;
92,8,16;
11,93,7;
93,6,7;
45,94,46;
94,24,46;
45,25,94;
94,25,24;
6,95,26;
9,26,95;
26,96,30;
96,9,30;
26,95,96;
96,95,9;
15,97,16;
97,7,16;
15,11,97;
97,11,7;
17,98,39;
98,18,39;
17,20,98;
98,20,18;
15,99,34;
99,23,34;
15,16,99;
99,16,23;
4,100,33;
100,11,33;
32,101,41;
101,14,41;
32,20,101;
101,20,14;
27,102,26;
102,12,26;
27,8,102;
102,8,12;
18,22,103;
103,39,18;
22,5,103;
103,5,39;
18,104,103;
104,22,103;
18,21,104;
21,22,104;
22,105,8;
105,21,8;
22,104,105;
105,104,21;
29,106,24;
106,37,24;
29,42,106;
106,42,37;
31,9,107;
107,1,31;
9,108,30;
108,31,30;
9,107,108;
108,107,31;
30,109,29;
109,42,29;
30,31,109;
31,42,109;
38,42,110;
31,38,110;
42,109,110;
110,109,31;
38,111,110;
111,42,110;
38,28,111;
111,28,42;
27,112,29;
112,30,29;
27,26,112;
112,26,30;
37,113,43;
113,28,43;
37,42,113;
113,42,28;
43,114,37;
114,47,37;
43,10,114;
114,10,47;
15,115,33;
115,36,33;
15,34,115;
115,34,36;
31,116,110;
116,38,110;
31,1,116;
116,1,38;
13,117,41;
117,19,41;
64,118,62;
68,62,118;
64,40,118;
118,40,68;
56,119,74;
119,39,74;
56,67,119;
119,67,39;
10,120,47;
120,54,47;
10,48,120;
48,54,120;
48,121,120;
121,54,120;
48,53,121;
53,54,121;
54,122,76;
122,53,76;
54,121,122;
122,121,53;
64,123,72;
123,63,72;
64,65,123;
123,65,63;
60,124,80;
124,59,80;
60,61,124;
61,59,124;
59,125,50;
61,50,125;
59,124,125;
125,124,61;
61,126,125;
126,50,125;
61,57,126;
126,57,50;
62,127,56;
127,67,56;
62,59,127;
127,59,67;
80,62,128;
128,68,80;
62,118,128;
128,118,68;
63,129,84;
129,82,84;
63,85,129;
129,85,82;
62,130,59;
130,80,59;
62,128,130;
130,128,80;
71,3,131;
131,51,71;
3,132,78;
132,71,78;
3,131,132;
132,131,71;
63,133,85;
66,85,133;
63,65,133;
65,66,133;
66,134,133;
134,85,133;
66,89,134;
134,89,85;
66,135,74;
65,74,135;
66,133,135;
135,133,65;
65,136,135;
136,74,135;
65,56,136;
136,56,74;
82,137,84;
137,73,84;
82,58,137;
137,58,73;
58,138,88;
82,88,138;
58,137,138;
138,137,82;
52,139,40;
70,40,139;
70,140,139;
140,40,139;
70,68,140;
140,68,40;
81,68,141;
141,70,81;
68,140,141;
141,140,70;
82,142,138;
142,88,138;
82,86,142;
142,86,88;
77,143,83;
143,49,83;
77,53,143;
143,53,49;
87,144,2;
144,83,2;
87,88,144;
144,88,83;
68,145,79;
145,81,79;
68,141,145;
145,141,81;
87,146,88;
146,58,88;
85,147,82;
147,86,82;
85,75,147;
147,75,86;
77,148,86;
148,88,86;
77,83,148;
148,83,88;
];
figure;trimesh(triangles, nodes(:,1), nodes(:,2));
