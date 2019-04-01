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
0.222813,0.560782;
0,0.625;
0.379323,0.337901;
0.253461,0.337055;
0,0.375;
0.03125,0.4375;
0.03125,0.3125;
0.105469,0.685547;
0.0742187,0.748047;
0.452312,0.656049;
0.45138,0.707629;
0.48145,0.749547;
0.409938,0.432706;
0.211629,0.723405;
0.1875,1;
0,0.875;
0.0387798,0.9375;
0.361231,0.835786;
0.32491,0.664785;
0.599152,0.705614;
0.411128,0.875956;
0.470675,0.85438;
0.159076,0.431441;
0.221576,0.431441;
0.423787,0.549645;
0.375,0.564846;
0.330884,0.545114;
0.3125,0.50042;
0.280794,0.645053;
0.282837,0.202024;
0.329213,0.226991;
0,0.125;
0.0283783,0.1875;
0.161313,0.189626;
0.134324,0.126514;
0.168445,0.0640138;
0.151944,0.307053;
0.297328,0.0713766;
0.423905,0.0631556;
0.167709,0.825534;
0.209962,0.843871;
0.10128,0.9375;
0.331161,0.793868;
0.303039,0.75739;
0.0908783,0.0625;
0.566537,0.946455;
0.375,1;
0.44449,0.968031;
0.31949,0.968031;
0.6875,0;
0.841356,0.669396;
0.496139,0.315781;
0.540733,0.337095;
0.585263,0.359668;
0.510106,0.19665;
0.445324,0.184775;
0.55752,0.584718;
0.532182,0.546342;
0.543803,0.627351;
0.542501,0.0581045;
0.605001,0.0581045;
0.636251,0.0928451;
0.955756,0.446176;
0.875,0;
0.815107,0.513486;
0.709033,0.790001;
0.648474,0.798862;
0.582167,0.829485;
0.675647,0.646132;
0.795567,0.694165;
0.835996,0.376499;
0.747909,0.696569;
0.689135,0.934871;
0.749694,0.926009;
0.812194,0.888755;
0.689364,0.603498;
0.738726,0.582378;
0.875,1;
0.9375,0.962745;
0.71759,0.426206;
0.70437,0.378429;
0.706197,0.328539;
0.686999,0.470329;
0.666491,0.511489;
0.93481,0.34375;
0.93481,0.28125;
1,0.625;
0.962285,0.6875;
0.927436,0.751159;
0.962285,0.5625;
1,0.8125;
0.799594,0.799486;
0.562928,0.450717;
0.9375,0.900245;
0.892387,0.25;
0.609746,0.219223;
0.856942,0.416425;
0.654275,0.241796;
0.762137,0.0673734;
0.9375,0.0860206;
0.892091,0.782409;
0.902155,0.868995;
1,0.1875;
0.796535,0.285573;
0.844714,0.161123;
];
triangles = [77,75,76;
6,26,12;
16,12,8;
11,6,7;
24,45,25;
22,8,25;
24,27,29;
12,7,6;
6,9,26;
42,38,28;
14,17,50;
7,15,11;
18,17,20;
16,8,21;
45,22,25;
23,15,16;
15,23,34;
15,7,16;
11,15,33;
57,14,50;
12,16,7;
22,18,21;
19,35,36;
4,11,33;
20,17,14;
14,32,20;
23,18,20;
17,18,39;
13,41,57;
17,59,50;
22,21,8;
32,14,41;
12,27,8;
39,22,5;
21,23,16;
18,23,21;
27,24,25;
37,29,42;
27,12,26;
24,37,46;
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
4,33,35;
20,34,23;
36,34,32;
15,36,33;
35,33,36;
19,36,32;
47,46,37;
22,39,18;
38,31,1;
74,39,5;
85,66,89;
57,55,13;
13,19,41;
41,19,32;
30,42,29;
42,31,38;
48,49,53;
37,28,43;
68,64,40;
69,44,89;
22,45,5;
43,47,37;
44,45,46;
44,47,54;
47,44,46;
54,48,53;
39,56,67;
59,17,67;
54,10,48;
51,60,71;
55,57,61;
41,14,57;
84,52,72;
50,61,57;
49,2,83;
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
51,61,60;
62,56,65;
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
45,44,69;
74,69,66;
52,40,72;
62,65,64;
3,71,78;
79,80,68;
88,82,86;
71,60,79;
75,77,86;
82,73,84;
69,74,5;
66,65,74;
76,44,54;
63,82,84;
77,76,53;
89,76,75;
49,77,53;
83,87,88;
68,70,81;
81,71,79;
60,59,80;
62,80,59;
78,71,81;
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
44,76,89;
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
8,16,92;
16,93,21;
93,8,21;
16,92,93;
93,92,8;
11,94,7;
94,6,7;
45,95,46;
95,24,46;
45,25,95;
95,25,24;
27,96,25;
96,24,25;
27,29,96;
96,29,24;
26,6,97;
9,26,97;
26,98,97;
98,6,97;
26,12,98;
98,12,6;
26,99,30;
99,9,30;
26,97,99;
99,97,9;
15,100,16;
100,7,16;
15,11,100;
100,11,7;
11,101,33;
101,15,33;
11,100,101;
101,100,15;
17,102,39;
102,18,39;
17,20,102;
102,20,18;
20,103,14;
17,14,103;
20,102,103;
103,102,17;
17,104,103;
104,14,103;
17,50,104;
104,50,14;
22,105,5;
105,45,5;
22,25,105;
105,25,45;
15,106,34;
106,23,34;
15,16,106;
106,16,23;
19,107,36;
107,35,36;
33,4,108;
108,11,33;
4,109,35;
33,35,109;
4,108,109;
109,108,33;
32,110,41;
14,41,110;
32,20,110;
110,20,14;
18,111,21;
23,21,111;
18,20,111;
111,20,23;
59,112,67;
112,17,67;
59,50,112;
112,50,17;
41,113,57;
14,57,113;
41,110,113;
113,110,14;
14,114,113;
114,57,113;
14,50,114;
114,50,57;
27,115,26;
115,12,26;
27,8,115;
115,8,12;
8,116,25;
116,27,25;
8,115,116;
116,115,27;
18,22,117;
117,39,18;
22,5,117;
117,5,39;
18,118,117;
118,22,117;
18,21,118;
21,22,118;
8,22,119;
119,21,8;
22,118,119;
119,118,21;
8,120,119;
120,22,119;
8,25,120;
120,25,22;
23,121,111;
121,21,111;
23,16,121;
121,16,21;
29,122,24;
37,24,122;
29,42,122;
122,42,37;
37,123,122;
123,24,122;
37,46,123;
123,46,24;
31,9,124;
124,1,31;
9,125,30;
125,31,30;
9,124,125;
125,124,31;
30,126,29;
126,42,29;
30,31,126;
31,42,126;
38,42,127;
31,38,127;
42,126,127;
127,126,31;
38,128,127;
128,42,127;
38,28,128;
128,28,42;
27,129,29;
129,30,29;
27,26,129;
129,26,30;
37,130,43;
130,28,43;
37,42,130;
130,42,28;
43,131,37;
131,47,37;
43,10,131;
131,10,47;
15,132,33;
132,36,33;
15,34,132;
34,36,132;
36,133,32;
133,34,32;
36,132,133;
133,132,34;
35,134,36;
134,33,36;
35,109,134;
134,109,33;
34,20,135;
135,32,34;
20,110,135;
135,110,32;
20,136,23;
136,34,23;
20,135,136;
136,135,34;
31,137,127;
137,38,127;
31,1,137;
137,1,38;
55,138,61;
138,57,61;
55,13,138;
138,13,57;
41,13,139;
19,41,139;
41,140,139;
140,13,139;
41,57,140;
140,57,13;
41,141,32;
141,19,32;
41,139,141;
141,139,19;
48,142,53;
142,49,53;
64,143,62;
68,62,143;
64,40,143;
143,40,68;
45,144,69;
44,69,144;
45,46,144;
144,46,44;
44,145,144;
145,69,144;
44,89,145;
89,69,145;
69,146,66;
146,89,66;
69,145,146;
146,145,89;
46,47,147;
147,44,46;
47,54,147;
147,54,44;
46,148,147;
148,47,147;
46,37,148;
148,37,47;
56,149,74;
39,74,149;
56,67,149;
67,39,149;
39,150,149;
150,74,149;
39,5,150;
150,5,74;
39,151,17;
151,67,17;
39,149,151;
151,149,67;
10,152,47;
152,54,47;
10,48,152;
48,54,152;
48,153,152;
153,54,152;
48,53,153;
53,54,153;
54,154,76;
154,53,76;
54,153,154;
154,153,53;
52,155,73;
155,84,73;
52,72,155;
155,72,84;
49,156,83;
156,2,83;
64,157,72;
157,63,72;
64,65,157;
157,65,63;
60,158,80;
158,59,80;
60,61,158;
61,59,158;
59,159,50;
61,50,159;
59,158,159;
159,158,61;
61,160,159;
160,50,159;
61,57,160;
160,57,50;
56,62,161;
161,67,56;
62,59,161;
161,59,67;
80,62,162;
162,68,80;
62,143,162;
162,143,68;
84,63,163;
163,82,84;
63,85,163;
163,85,82;
62,164,59;
164,80,59;
62,162,164;
164,162,80;
60,51,165;
165,61,60;
51,55,165;
165,55,61;
60,166,165;
166,51,165;
60,71,166;
166,71,51;
71,167,79;
167,60,79;
71,166,167;
167,166,60;
56,168,161;
168,62,161;
56,65,168;
65,62,168;
62,169,64;
169,65,64;
62,168,169;
169,168,65;
71,3,170;
170,51,71;
3,171,78;
71,78,171;
3,170,171;
171,170,71;
63,172,85;
66,85,172;
63,65,172;
65,66,172;
66,173,172;
173,85,172;
66,89,173;
89,85,173;
85,174,75;
174,89,75;
85,173,174;
174,173,89;
66,175,74;
65,74,175;
66,172,175;
175,172,65;
65,176,175;
176,74,175;
65,56,176;
176,56,74;
82,177,84;
177,73,84;
82,58,177;
177,58,73;
58,178,88;
82,88,178;
58,177,178;
178,177,82;
40,52,179;
70,40,179;
70,180,179;
180,40,179;
70,68,180;
180,68,40;
81,68,181;
181,70,81;
68,180,181;
181,180,70;
52,182,72;
182,40,72;
52,179,182;
182,179,40;
70,183,81;
183,78,81;
79,184,68;
184,80,68;
79,60,184;
184,60,80;
69,185,5;
185,74,5;
69,66,185;
185,66,74;
78,186,81;
71,81,186;
78,171,186;
186,171,71;
82,187,178;
187,88,178;
82,86,187;
187,86,88;
44,188,89;
76,89,188;
44,54,188;
188,54,76;
63,189,72;
189,84,72;
63,163,189;
189,163,84;
76,190,188;
190,89,188;
76,75,190;
190,75,89;
77,191,83;
191,49,83;
77,53,191;
191,53,49;
87,192,2;
192,83,2;
87,88,192;
192,88,83;
68,193,79;
193,81,79;
68,181,193;
193,181,81;
71,194,186;
194,81,186;
71,79,194;
194,79,81;
87,195,88;
195,58,88;
85,196,82;
196,86,82;
85,75,196;
196,75,86;
77,197,86;
197,88,86;
77,83,197;
197,83,88;
];
figure;trimesh(triangles, nodes(:,1), nodes(:,2));
