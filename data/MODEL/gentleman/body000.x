xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 172;
 0.00000;8.74009;0.00000;,
 2.90800;8.74009;-7.50640;,
 0.00000;8.74009;-8.05000;,
 5.42325;8.74009;-5.94902;,
 7.20606;8.74009;-3.58819;,
 8.01566;8.74009;-0.74276;,
 7.74270;8.74009;2.20299;,
 6.42404;8.74009;4.85121;,
 4.23778;8.74009;6.84425;,
 1.47918;8.74009;7.91293;,
 -1.47918;8.74009;7.91293;,
 -4.23778;8.74009;6.84425;,
 -6.42404;8.74009;4.85121;,
 -7.74270;8.74009;2.20299;,
 -8.01566;8.74009;-0.74276;,
 -7.20606;8.74009;-3.58820;,
 -5.42325;8.74009;-5.94903;,
 -2.90799;8.74009;-7.50640;,
 3.18448;8.60704;-8.22009;,
 0.00000;8.60704;-8.81537;,
 5.93887;8.60704;-6.51463;,
 7.89119;8.60704;-3.92935;,
 8.77776;8.60704;-0.81338;,
 8.47885;8.60704;2.41244;,
 7.03481;8.60704;5.31245;,
 4.64069;8.60704;7.49498;,
 1.61982;8.60704;8.66527;,
 -1.61982;8.60704;8.66527;,
 -4.64069;8.60704;7.49498;,
 -7.03481;8.60704;5.31245;,
 -8.47885;8.60704;2.41244;,
 -8.77776;8.60704;-0.81338;,
 -7.89119;8.60704;-3.92935;,
 -5.93887;8.60704;-6.51464;,
 -3.18447;8.60704;-8.22009;,
 3.41887;8.22812;-8.82512;,
 0.00000;8.22812;-9.46421;,
 6.37600;8.22812;-6.99414;,
 8.47202;8.22812;-4.21856;,
 9.42384;8.22812;-0.87325;,
 9.10292;8.22812;2.59000;,
 7.55261;8.22812;5.70346;,
 4.98227;8.22812;8.04664;,
 1.73904;8.22812;9.30307;,
 -1.73904;8.22812;9.30307;,
 -4.98227;8.22812;8.04664;,
 -7.55260;8.22812;5.70346;,
 -9.10292;8.22812;2.59000;,
 -9.42384;8.22812;-0.87325;,
 -8.47201;8.22812;-4.21857;,
 -6.37599;8.22812;-6.99414;,
 -3.41886;8.22812;-8.82512;,
 3.57548;7.66102;-9.22939;,
 0.00000;7.66102;-9.89776;,
 6.66808;7.66102;-7.31453;,
 8.86011;7.66102;-4.41181;,
 9.85554;7.66102;-0.91325;,
 9.51992;7.66102;2.70865;,
 7.89858;7.66102;5.96473;,
 5.21050;7.66102;8.41524;,
 1.81871;7.66102;9.72923;,
 -1.81871;7.66102;9.72923;,
 -5.21050;7.66102;8.41525;,
 -7.89858;7.66102;5.96473;,
 -9.51992;7.66102;2.70865;,
 -9.85554;7.66102;-0.91325;,
 -8.86011;7.66102;-4.41182;,
 -6.66807;7.66102;-7.31454;,
 -3.57547;7.66102;-9.22939;,
 3.63048;6.99208;-9.37135;,
 0.00000;6.99208;-10.05000;,
 6.77064;6.99208;-7.42704;,
 8.99639;6.99208;-4.47967;,
 10.00713;6.99208;-0.92730;,
 9.66635;6.99208;2.75031;,
 8.02007;6.99208;6.05648;,
 5.29064;6.99208;8.54468;,
 1.84668;6.99208;9.87888;,
 -1.84668;6.99208;9.87888;,
 -5.29064;6.99208;8.54468;,
 -8.02007;6.99208;6.05648;,
 -9.66635;6.99208;2.75031;,
 -10.00713;6.99208;-0.92730;,
 -8.99639;6.99208;-4.47967;,
 -6.77064;6.99208;-7.42704;,
 -3.63047;6.99208;-9.37135;,
 3.63048;-6.99208;-9.37135;,
 0.00000;-6.99208;-10.05000;,
 6.77064;-6.99208;-7.42704;,
 8.99639;-6.99208;-4.47967;,
 10.00713;-6.99208;-0.92730;,
 9.66635;-6.99208;2.75031;,
 8.02007;-6.99208;6.05648;,
 5.29064;-6.99208;8.54468;,
 1.84668;-6.99208;9.87888;,
 -1.84668;-6.99208;9.87888;,
 -5.29064;-6.99208;8.54468;,
 -8.02007;-6.99208;6.05648;,
 -9.66635;-6.99208;2.75031;,
 -10.00713;-6.99208;-0.92730;,
 -8.99639;-6.99208;-4.47967;,
 -6.77064;-6.99208;-7.42704;,
 -3.63047;-6.99208;-9.37135;,
 3.57548;-7.66102;-9.22939;,
 0.00000;-7.66102;-9.89776;,
 6.66808;-7.66102;-7.31453;,
 8.86011;-7.66102;-4.41181;,
 9.85554;-7.66102;-0.91325;,
 9.51992;-7.66102;2.70865;,
 7.89858;-7.66102;5.96473;,
 5.21050;-7.66102;8.41524;,
 1.81871;-7.66102;9.72923;,
 -1.81871;-7.66102;9.72923;,
 -5.21050;-7.66102;8.41525;,
 -7.89858;-7.66102;5.96473;,
 -9.51992;-7.66102;2.70865;,
 -9.85554;-7.66102;-0.91325;,
 -8.86011;-7.66102;-4.41182;,
 -6.66807;-7.66102;-7.31454;,
 -3.57547;-7.66102;-9.22939;,
 3.41887;-8.22812;-8.82512;,
 0.00000;-8.22812;-9.46421;,
 6.37600;-8.22812;-6.99414;,
 8.47202;-8.22812;-4.21856;,
 9.42384;-8.22812;-0.87325;,
 9.10292;-8.22812;2.59000;,
 7.55261;-8.22812;5.70346;,
 4.98227;-8.22812;8.04664;,
 1.73904;-8.22812;9.30307;,
 -1.73904;-8.22812;9.30307;,
 -4.98227;-8.22812;8.04664;,
 -7.55260;-8.22812;5.70346;,
 -9.10292;-8.22812;2.59000;,
 -9.42384;-8.22812;-0.87325;,
 -8.47201;-8.22812;-4.21857;,
 -6.37599;-8.22812;-6.99414;,
 -3.41886;-8.22812;-8.82512;,
 3.18448;-8.60704;-8.22009;,
 0.00000;-8.60704;-8.81537;,
 5.93887;-8.60704;-6.51463;,
 7.89119;-8.60704;-3.92935;,
 8.77776;-8.60704;-0.81338;,
 8.47885;-8.60704;2.41244;,
 7.03481;-8.60704;5.31245;,
 4.64069;-8.60704;7.49498;,
 1.61982;-8.60704;8.66527;,
 -1.61982;-8.60704;8.66527;,
 -4.64069;-8.60704;7.49498;,
 -7.03481;-8.60704;5.31245;,
 -8.47885;-8.60704;2.41244;,
 -8.77776;-8.60704;-0.81338;,
 -7.89119;-8.60704;-3.92935;,
 -5.93887;-8.60704;-6.51464;,
 -3.18447;-8.60704;-8.22009;,
 2.90800;-8.74009;-7.50640;,
 0.00000;-8.74009;-8.05000;,
 5.42325;-8.74009;-5.94902;,
 7.20606;-8.74009;-3.58819;,
 8.01566;-8.74009;-0.74276;,
 7.74270;-8.74009;2.20299;,
 6.42404;-8.74009;4.85121;,
 4.23778;-8.74009;6.84425;,
 1.47918;-8.74009;7.91293;,
 -1.47918;-8.74009;7.91293;,
 -4.23778;-8.74009;6.84425;,
 -6.42404;-8.74009;4.85121;,
 -7.74270;-8.74009;2.20299;,
 -8.01566;-8.74009;-0.74276;,
 -7.20606;-8.74009;-3.58820;,
 -5.42325;-8.74009;-5.94903;,
 -2.90799;-8.74009;-7.50640;,
 0.00000;-8.74009;-0.00000;;
 
 187;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,9,8;,
 3;0,10,9;,
 3;0,11,10;,
 3;0,12,11;,
 3;0,13,12;,
 3;0,14,13;,
 3;0,15,14;,
 3;0,16,15;,
 3;0,17,16;,
 3;0,2,17;,
 4;2,1,18,19;,
 4;1,3,20,18;,
 4;3,4,21,20;,
 4;4,5,22,21;,
 4;5,6,23,22;,
 4;6,7,24,23;,
 4;7,8,25,24;,
 4;8,9,26,25;,
 4;9,10,27,26;,
 4;10,11,28,27;,
 4;11,12,29,28;,
 4;12,13,30,29;,
 4;13,14,31,30;,
 4;14,15,32,31;,
 4;15,16,33,32;,
 4;16,17,34,33;,
 4;17,2,19,34;,
 4;19,18,35,36;,
 4;18,20,37,35;,
 4;20,21,38,37;,
 4;21,22,39,38;,
 4;22,23,40,39;,
 4;23,24,41,40;,
 4;24,25,42,41;,
 4;25,26,43,42;,
 4;26,27,44,43;,
 4;27,28,45,44;,
 4;28,29,46,45;,
 4;29,30,47,46;,
 4;30,31,48,47;,
 4;31,32,49,48;,
 4;32,33,50,49;,
 4;33,34,51,50;,
 4;34,19,36,51;,
 4;36,35,52,53;,
 4;35,37,54,52;,
 4;37,38,55,54;,
 4;38,39,56,55;,
 4;39,40,57,56;,
 4;40,41,58,57;,
 4;41,42,59,58;,
 4;42,43,60,59;,
 4;43,44,61,60;,
 4;44,45,62,61;,
 4;45,46,63,62;,
 4;46,47,64,63;,
 4;47,48,65,64;,
 4;48,49,66,65;,
 4;49,50,67,66;,
 4;50,51,68,67;,
 4;51,36,53,68;,
 4;53,52,69,70;,
 4;52,54,71,69;,
 4;54,55,72,71;,
 4;55,56,73,72;,
 4;56,57,74,73;,
 4;57,58,75,74;,
 4;58,59,76,75;,
 4;59,60,77,76;,
 4;60,61,78,77;,
 4;61,62,79,78;,
 4;62,63,80,79;,
 4;63,64,81,80;,
 4;64,65,82,81;,
 4;65,66,83,82;,
 4;66,67,84,83;,
 4;67,68,85,84;,
 4;68,53,70,85;,
 4;70,69,86,87;,
 4;69,71,88,86;,
 4;71,72,89,88;,
 4;72,73,90,89;,
 4;73,74,91,90;,
 4;74,75,92,91;,
 4;75,76,93,92;,
 4;76,77,94,93;,
 4;77,78,95,94;,
 4;78,79,96,95;,
 4;79,80,97,96;,
 4;80,81,98,97;,
 4;81,82,99,98;,
 4;82,83,100,99;,
 4;83,84,101,100;,
 4;84,85,102,101;,
 4;85,70,87,102;,
 4;87,86,103,104;,
 4;86,88,105,103;,
 4;88,89,106,105;,
 4;89,90,107,106;,
 4;90,91,108,107;,
 4;91,92,109,108;,
 4;92,93,110,109;,
 4;93,94,111,110;,
 4;94,95,112,111;,
 4;95,96,113,112;,
 4;96,97,114,113;,
 4;97,98,115,114;,
 4;98,99,116,115;,
 4;99,100,117,116;,
 4;100,101,118,117;,
 4;101,102,119,118;,
 4;102,87,104,119;,
 4;104,103,120,121;,
 4;103,105,122,120;,
 4;105,106,123,122;,
 4;106,107,124,123;,
 4;107,108,125,124;,
 4;108,109,126,125;,
 4;109,110,127,126;,
 4;110,111,128,127;,
 4;111,112,129,128;,
 4;112,113,130,129;,
 4;113,114,131,130;,
 4;114,115,132,131;,
 4;115,116,133,132;,
 4;116,117,134,133;,
 4;117,118,135,134;,
 4;118,119,136,135;,
 4;119,104,121,136;,
 4;121,120,137,138;,
 4;120,122,139,137;,
 4;122,123,140,139;,
 4;123,124,141,140;,
 4;124,125,142,141;,
 4;125,126,143,142;,
 4;126,127,144,143;,
 4;127,128,145,144;,
 4;128,129,146,145;,
 4;129,130,147,146;,
 4;130,131,148,147;,
 4;131,132,149,148;,
 4;132,133,150,149;,
 4;133,134,151,150;,
 4;134,135,152,151;,
 4;135,136,153,152;,
 4;136,121,138,153;,
 4;138,137,154,155;,
 4;137,139,156,154;,
 4;139,140,157,156;,
 4;140,141,158,157;,
 4;141,142,159,158;,
 4;142,143,160,159;,
 4;143,144,161,160;,
 4;144,145,162,161;,
 4;145,146,163,162;,
 4;146,147,164,163;,
 4;147,148,165,164;,
 4;148,149,166,165;,
 4;149,150,167,166;,
 4;150,151,168,167;,
 4;151,152,169,168;,
 4;152,153,170,169;,
 4;153,138,155,170;,
 3;155,154,171;,
 3;154,156,171;,
 3;156,157,171;,
 3;157,158,171;,
 3;158,159,171;,
 3;159,160,171;,
 3;160,161,171;,
 3;161,162,171;,
 3;162,163,171;,
 3;163,164,171;,
 3;164,165,171;,
 3;165,166,171;,
 3;166,167,171;,
 3;167,168,171;,
 3;168,169,171;,
 3;169,170,171;,
 3;170,155,171;;
 
 MeshMaterialList {
  1;
  187;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.000000;0.530196;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  172;
  0.000000;1.000000;0.000000;,
  0.000000;0.996301;-0.085932;,
  0.031042;0.996301;-0.080129;,
  0.057892;0.996301;-0.063505;,
  0.076923;0.996301;-0.038303;,
  0.085566;0.996301;-0.007929;,
  0.082652;0.996301;0.023516;,
  0.068575;0.996301;0.051786;,
  0.045237;0.996301;0.073061;,
  0.015790;0.996301;0.084469;,
  -0.015790;0.996301;0.084469;,
  -0.045237;0.996301;0.073061;,
  -0.068575;0.996301;0.051786;,
  -0.082652;0.996301;0.023516;,
  -0.085566;0.996301;-0.007929;,
  -0.076923;0.996301;-0.038303;,
  -0.057892;0.996301;-0.063505;,
  -0.031042;0.996301;-0.080129;,
  0.000000;0.939375;-0.342891;,
  0.123866;0.939375;-0.319736;,
  0.231004;0.939375;-0.253399;,
  0.306943;0.939375;-0.152840;,
  0.341428;0.939375;-0.031638;,
  0.329801;0.939375;0.093836;,
  0.273633;0.939375;0.206638;,
  0.180509;0.939375;0.291531;,
  0.063006;0.939375;0.337052;,
  -0.063006;0.939375;0.337052;,
  -0.180509;0.939375;0.291532;,
  -0.273633;0.939375;0.206638;,
  -0.329801;0.939375;0.093836;,
  -0.341428;0.939375;-0.031638;,
  -0.306943;0.939375;-0.152840;,
  -0.231004;0.939375;-0.253399;,
  -0.123866;0.939375;-0.319736;,
  0.000000;0.750033;-0.661400;,
  0.238925;0.750033;-0.616738;,
  0.445583;0.750033;-0.488781;,
  0.592062;0.750033;-0.294812;,
  0.658579;0.750033;-0.061026;,
  0.636152;0.750033;0.181001;,
  0.527809;0.750033;0.398583;,
  0.348183;0.750033;0.562334;,
  0.121532;0.750033;0.650139;,
  -0.121532;0.750033;0.650139;,
  -0.348182;0.750033;0.562334;,
  -0.527809;0.750033;0.398583;,
  -0.636152;0.750033;0.181001;,
  -0.658579;0.750033;-0.061027;,
  -0.592062;0.750033;-0.294812;,
  -0.445582;0.750033;-0.488781;,
  -0.238925;0.750033;-0.616738;,
  0.000000;0.424887;-0.905246;,
  0.327013;0.424887;-0.844117;,
  0.609861;0.424887;-0.668985;,
  0.810343;0.424887;-0.403503;,
  0.901385;0.424887;-0.083526;,
  0.870689;0.424887;0.247732;,
  0.722402;0.424887;0.545533;,
  0.476551;0.424887;0.769656;,
  0.166339;0.424887;0.889833;,
  -0.166339;0.424887;0.889833;,
  -0.476551;0.424887;0.769656;,
  -0.722402;0.424887;0.545533;,
  -0.870689;0.424887;0.247732;,
  -0.901385;0.424887;-0.083526;,
  -0.810343;0.424887;-0.403503;,
  -0.609860;0.424887;-0.668986;,
  -0.327012;0.424887;-0.844117;,
  0.000000;0.111700;-0.993742;,
  0.358981;0.111700;-0.926637;,
  0.669480;0.111700;-0.734384;,
  0.889561;0.111700;-0.442949;,
  0.989503;0.111700;-0.091691;,
  0.955807;0.111700;0.271950;,
  0.793023;0.111700;0.598863;,
  0.523138;0.111700;0.844896;,
  0.182600;0.111699;0.976822;,
  -0.182599;0.111699;0.976822;,
  -0.523138;0.111699;0.844897;,
  -0.793023;0.111700;0.598863;,
  -0.955806;0.111700;0.271950;,
  -0.989503;0.111700;-0.091691;,
  -0.889561;0.111700;-0.442949;,
  -0.669479;0.111700;-0.734385;,
  -0.358980;0.111700;-0.926637;,
  0.000000;-0.111700;-0.993742;,
  0.358981;-0.111700;-0.926637;,
  0.669480;-0.111700;-0.734384;,
  0.889561;-0.111700;-0.442949;,
  0.989503;-0.111700;-0.091691;,
  0.955806;-0.111700;0.271950;,
  0.793023;-0.111700;0.598863;,
  0.523138;-0.111700;0.844897;,
  0.182600;-0.111699;0.976822;,
  -0.182599;-0.111699;0.976822;,
  -0.523138;-0.111699;0.844897;,
  -0.793023;-0.111700;0.598863;,
  -0.955806;-0.111700;0.271950;,
  -0.989503;-0.111700;-0.091691;,
  -0.889561;-0.111700;-0.442949;,
  -0.669479;-0.111700;-0.734385;,
  -0.358980;-0.111700;-0.926637;,
  0.000000;-0.424887;-0.905246;,
  0.327013;-0.424887;-0.844117;,
  0.609861;-0.424887;-0.668985;,
  0.810343;-0.424887;-0.403503;,
  0.901385;-0.424887;-0.083526;,
  0.870689;-0.424887;0.247732;,
  0.722402;-0.424887;0.545533;,
  0.476551;-0.424887;0.769656;,
  0.166339;-0.424887;0.889833;,
  -0.166339;-0.424887;0.889833;,
  -0.476551;-0.424887;0.769656;,
  -0.722402;-0.424887;0.545533;,
  -0.870689;-0.424887;0.247732;,
  -0.901385;-0.424887;-0.083526;,
  -0.810343;-0.424887;-0.403503;,
  -0.609860;-0.424887;-0.668986;,
  -0.327012;-0.424887;-0.844117;,
  0.000000;-0.750033;-0.661400;,
  0.238925;-0.750033;-0.616738;,
  0.445583;-0.750033;-0.488781;,
  0.592062;-0.750033;-0.294812;,
  0.658579;-0.750033;-0.061026;,
  0.636152;-0.750033;0.181001;,
  0.527809;-0.750033;0.398583;,
  0.348182;-0.750033;0.562334;,
  0.121532;-0.750033;0.650139;,
  -0.121532;-0.750033;0.650139;,
  -0.348182;-0.750033;0.562334;,
  -0.527809;-0.750033;0.398583;,
  -0.636152;-0.750033;0.181001;,
  -0.658579;-0.750033;-0.061027;,
  -0.592062;-0.750033;-0.294812;,
  -0.445583;-0.750033;-0.488781;,
  -0.238925;-0.750033;-0.616738;,
  0.000000;-0.939375;-0.342891;,
  0.123866;-0.939375;-0.319736;,
  0.231004;-0.939375;-0.253399;,
  0.306943;-0.939375;-0.152840;,
  0.341428;-0.939375;-0.031638;,
  0.329801;-0.939375;0.093836;,
  0.273633;-0.939375;0.206638;,
  0.180509;-0.939375;0.291531;,
  0.063006;-0.939375;0.337052;,
  -0.063006;-0.939375;0.337052;,
  -0.180509;-0.939375;0.291532;,
  -0.273633;-0.939375;0.206638;,
  -0.329801;-0.939375;0.093836;,
  -0.341428;-0.939375;-0.031638;,
  -0.306943;-0.939375;-0.152840;,
  -0.231004;-0.939375;-0.253399;,
  -0.123866;-0.939375;-0.319736;,
  0.000000;-0.996301;-0.085932;,
  0.031042;-0.996301;-0.080129;,
  0.057892;-0.996301;-0.063505;,
  0.076923;-0.996301;-0.038303;,
  0.085566;-0.996301;-0.007929;,
  0.082652;-0.996301;0.023516;,
  0.068575;-0.996301;0.051786;,
  0.045237;-0.996301;0.073061;,
  0.015790;-0.996301;0.084469;,
  -0.015790;-0.996301;0.084469;,
  -0.045237;-0.996301;0.073061;,
  -0.068575;-0.996301;0.051786;,
  -0.082652;-0.996301;0.023516;,
  -0.085566;-0.996301;-0.007929;,
  -0.076923;-0.996301;-0.038303;,
  -0.057892;-0.996301;-0.063505;,
  -0.031042;-0.996301;-0.080129;,
  0.000000;-1.000000;-0.000000;;
  187;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,12,11;,
  3;0,13,12;,
  3;0,14,13;,
  3;0,15,14;,
  3;0,16,15;,
  3;0,17,16;,
  3;0,1,17;,
  4;1,2,19,18;,
  4;2,3,20,19;,
  4;3,4,21,20;,
  4;4,5,22,21;,
  4;5,6,23,22;,
  4;6,7,24,23;,
  4;7,8,25,24;,
  4;8,9,26,25;,
  4;9,10,27,26;,
  4;10,11,28,27;,
  4;11,12,29,28;,
  4;12,13,30,29;,
  4;13,14,31,30;,
  4;14,15,32,31;,
  4;15,16,33,32;,
  4;16,17,34,33;,
  4;17,1,18,34;,
  4;18,19,36,35;,
  4;19,20,37,36;,
  4;20,21,38,37;,
  4;21,22,39,38;,
  4;22,23,40,39;,
  4;23,24,41,40;,
  4;24,25,42,41;,
  4;25,26,43,42;,
  4;26,27,44,43;,
  4;27,28,45,44;,
  4;28,29,46,45;,
  4;29,30,47,46;,
  4;30,31,48,47;,
  4;31,32,49,48;,
  4;32,33,50,49;,
  4;33,34,51,50;,
  4;34,18,35,51;,
  4;35,36,53,52;,
  4;36,37,54,53;,
  4;37,38,55,54;,
  4;38,39,56,55;,
  4;39,40,57,56;,
  4;40,41,58,57;,
  4;41,42,59,58;,
  4;42,43,60,59;,
  4;43,44,61,60;,
  4;44,45,62,61;,
  4;45,46,63,62;,
  4;46,47,64,63;,
  4;47,48,65,64;,
  4;48,49,66,65;,
  4;49,50,67,66;,
  4;50,51,68,67;,
  4;51,35,52,68;,
  4;52,53,70,69;,
  4;53,54,71,70;,
  4;54,55,72,71;,
  4;55,56,73,72;,
  4;56,57,74,73;,
  4;57,58,75,74;,
  4;58,59,76,75;,
  4;59,60,77,76;,
  4;60,61,78,77;,
  4;61,62,79,78;,
  4;62,63,80,79;,
  4;63,64,81,80;,
  4;64,65,82,81;,
  4;65,66,83,82;,
  4;66,67,84,83;,
  4;67,68,85,84;,
  4;68,52,69,85;,
  4;69,70,87,86;,
  4;70,71,88,87;,
  4;71,72,89,88;,
  4;72,73,90,89;,
  4;73,74,91,90;,
  4;74,75,92,91;,
  4;75,76,93,92;,
  4;76,77,94,93;,
  4;77,78,95,94;,
  4;78,79,96,95;,
  4;79,80,97,96;,
  4;80,81,98,97;,
  4;81,82,99,98;,
  4;82,83,100,99;,
  4;83,84,101,100;,
  4;84,85,102,101;,
  4;85,69,86,102;,
  4;86,87,104,103;,
  4;87,88,105,104;,
  4;88,89,106,105;,
  4;89,90,107,106;,
  4;90,91,108,107;,
  4;91,92,109,108;,
  4;92,93,110,109;,
  4;93,94,111,110;,
  4;94,95,112,111;,
  4;95,96,113,112;,
  4;96,97,114,113;,
  4;97,98,115,114;,
  4;98,99,116,115;,
  4;99,100,117,116;,
  4;100,101,118,117;,
  4;101,102,119,118;,
  4;102,86,103,119;,
  4;103,104,121,120;,
  4;104,105,122,121;,
  4;105,106,123,122;,
  4;106,107,124,123;,
  4;107,108,125,124;,
  4;108,109,126,125;,
  4;109,110,127,126;,
  4;110,111,128,127;,
  4;111,112,129,128;,
  4;112,113,130,129;,
  4;113,114,131,130;,
  4;114,115,132,131;,
  4;115,116,133,132;,
  4;116,117,134,133;,
  4;117,118,135,134;,
  4;118,119,136,135;,
  4;119,103,120,136;,
  4;120,121,138,137;,
  4;121,122,139,138;,
  4;122,123,140,139;,
  4;123,124,141,140;,
  4;124,125,142,141;,
  4;125,126,143,142;,
  4;126,127,144,143;,
  4;127,128,145,144;,
  4;128,129,146,145;,
  4;129,130,147,146;,
  4;130,131,148,147;,
  4;131,132,149,148;,
  4;132,133,150,149;,
  4;133,134,151,150;,
  4;134,135,152,151;,
  4;135,136,153,152;,
  4;136,120,137,153;,
  4;137,138,155,154;,
  4;138,139,156,155;,
  4;139,140,157,156;,
  4;140,141,158,157;,
  4;141,142,159,158;,
  4;142,143,160,159;,
  4;143,144,161,160;,
  4;144,145,162,161;,
  4;145,146,163,162;,
  4;146,147,164,163;,
  4;147,148,165,164;,
  4;148,149,166,165;,
  4;149,150,167,166;,
  4;150,151,168,167;,
  4;151,152,169,168;,
  4;152,153,170,169;,
  4;153,137,154,170;,
  3;154,155,171;,
  3;155,156,171;,
  3;156,157,171;,
  3;157,158,171;,
  3;158,159,171;,
  3;159,160,171;,
  3;160,161,171;,
  3;161,162,171;,
  3;162,163,171;,
  3;163,164,171;,
  3;164,165,171;,
  3;165,166,171;,
  3;166,167,171;,
  3;167,168,171;,
  3;168,169,171;,
  3;169,170,171;,
  3;170,154,171;;
 }
 MeshTextureCoords {
  172;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
