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
 245;
 -0.05019;0.05258;-0.28018;,
 0.14916;0.02759;0.15409;,
 -0.49234;0.12520;0.20048;,
 -0.32634;0.28241;0.68992;,
 -0.49234;0.12520;0.20048;,
 0.14916;0.02759;0.15409;,
 0.17080;0.29705;0.76448;,
 -0.32634;0.28241;0.68992;,
 0.14916;0.02759;0.15409;,
 0.56247;0.27652;0.47729;,
 0.17080;0.29705;0.76448;,
 0.14916;0.02759;0.15409;,
 0.78642;0.33472;-0.01085;,
 0.56247;0.27652;0.47729;,
 0.14916;0.02759;0.15409;,
 0.53604;0.28241;-0.49706;,
 0.78642;0.33472;-0.01085;,
 -0.05019;0.05258;-0.28018;,
 -0.05019;0.05258;-0.28018;,
 0.18682;0.30883;-0.74061;,
 0.53604;0.28241;-0.49706;,
 -0.05019;0.05258;-0.28018;,
 -0.38950;0.29419;-0.61751;,
 0.18682;0.30883;-0.74061;,
 -0.05019;0.05258;-0.28018;,
 -0.76086;0.30883;-0.16651;,
 -0.38950;0.29419;-0.61751;,
 -0.49234;0.12520;0.20048;,
 -0.32634;0.28241;0.68992;,
 -0.84904;0.53984;0.45290;,
 -0.49234;0.12520;0.20048;,
 -0.49234;0.12520;0.20048;,
 -0.84904;0.53984;0.45290;,
 -0.76086;0.30883;-0.16651;,
 0.17080;0.29705;0.76448;,
 0.00003;0.70028;1.06570;,
 -0.32634;0.28241;0.68992;,
 -0.38950;0.29419;-0.61751;,
 -0.16351;0.69646;-1.00577;,
 0.18682;0.30883;-0.74061;,
 -1.02601;0.69646;-0.14327;,
 -0.32634;0.28241;0.68992;,
 -0.47458;0.69265;0.95176;,
 -0.84904;0.53984;0.45290;,
 -0.47458;0.69265;0.95176;,
 0.17080;0.29705;0.76448;,
 0.41381;0.87767;1.02914;,
 0.00003;0.70028;1.06570;,
 0.56247;0.27652;0.47729;,
 0.56247;0.27652;0.47729;,
 0.93152;0.69265;0.49489;,
 0.41381;0.87767;1.02914;,
 0.78642;0.33472;-0.01085;,
 0.78642;0.33472;-0.01085;,
 1.08636;0.87767;0.10851;,
 0.93152;0.69265;0.49489;,
 0.78642;0.33472;-0.01085;,
 0.96834;0.87767;-0.47310;,
 0.53604;0.28241;-0.49706;,
 0.53604;0.28241;-0.49706;,
 0.49341;0.87767;-0.94803;,
 0.96834;0.87767;-0.47310;,
 0.18682;0.30883;-0.74061;,
 0.49341;0.87767;-0.94803;,
 -0.38950;0.29419;-0.61751;,
 -0.73920;0.69265;-0.71895;,
 -0.16351;0.69646;-1.00577;,
 -0.76086;0.30883;-0.16651;,
 -1.02601;0.69646;-0.14327;,
 -0.73920;0.69265;-0.71895;,
 -0.38950;0.29419;-0.61751;,
 -0.84904;0.53984;0.45290;,
 -0.79764;1.06268;0.81795;,
 -1.08681;1.33945;0.28064;,
 -0.47458;0.69265;0.95176;,
 -0.47458;0.69265;0.95176;,
 -0.26033;1.33945;1.10712;,
 -0.79764;1.06268;0.81795;,
 0.00003;0.70028;1.06570;,
 0.93152;0.69265;0.49489;,
 0.79770;1.06268;0.81795;,
 0.41381;0.87767;1.02914;,
 0.93152;0.69265;0.49489;,
 1.08636;0.87767;0.10851;,
 0.79770;1.06268;0.81795;,
 -0.73920;0.69265;-0.71895;,
 -0.51210;1.06268;-0.98485;,
 -0.16351;0.69646;-1.00577;,
 -0.73920;0.69265;-0.71895;,
 -1.00509;1.06268;-0.49186;,
 -0.51210;1.06268;-0.98485;,
 -1.02601;0.69646;-0.14327;,
 -0.84904;0.53984;0.45290;,
 -1.08681;1.33945;0.28064;,
 -1.02601;0.69646;-0.14327;,
 0.41381;0.87767;1.02914;,
 -0.26033;1.33945;1.10712;,
 0.00003;0.70028;1.06570;,
 -0.16351;0.69646;-1.00577;,
 0.00003;1.27712;-1.12186;,
 0.49341;0.87767;-0.94803;,
 -1.08681;1.33945;0.28064;,
 -1.00509;1.06268;-0.49186;,
 -0.79764;1.06268;0.81795;,
 -0.77800;1.50899;0.79830;,
 -1.08681;1.33945;0.28064;,
 -0.26033;1.33945;1.10712;,
 -0.77800;1.50899;0.79830;,
 -0.79764;1.06268;0.81795;,
 0.41381;0.87767;1.02914;,
 0.49956;1.50899;1.00065;,
 -0.26033;1.33945;1.10712;,
 0.79770;1.06268;0.81795;,
 0.79770;1.06268;0.81795;,
 0.98041;1.50899;0.51980;,
 0.49956;1.50899;1.00065;,
 1.08636;0.87767;0.10851;,
 1.08636;0.87767;0.10851;,
 1.08678;1.50899;-0.15185;,
 0.98041;1.50899;0.51980;,
 0.96834;0.87767;-0.47310;,
 1.08678;1.50899;-0.15185;,
 0.96834;0.87767;-0.47310;,
 0.77806;1.50899;-0.75775;,
 0.49341;0.87767;-0.94803;,
 0.34428;1.50899;-1.03922;,
 0.77806;1.50899;-0.75775;,
 -0.51210;1.06268;-0.98485;,
 -0.34422;1.50899;-1.03921;,
 0.00003;1.27712;-1.12186;,
 -0.51210;1.06268;-0.98485;,
 -0.77800;1.50899;-0.75775;,
 -1.00509;1.06268;-0.49186;,
 -1.05894;1.63147;-0.15185;,
 -0.77800;1.50899;-0.75775;,
 0.00003;1.94284;1.01437;,
 0.00003;1.94284;-0.97382;,
 0.34428;1.50899;-1.03922;,
 -0.77800;1.50899;0.79830;,
 -0.85963;2.00537;0.45829;,
 -1.08681;1.33945;0.28064;,
 -0.77800;1.50899;0.79830;,
 -0.43799;2.00537;0.87993;,
 -0.85963;2.00537;0.45829;,
 -0.26033;1.33945;1.10712;,
 -0.43799;2.00537;0.87993;,
 0.49956;1.50899;1.00065;,
 0.43805;2.00537;0.87993;,
 0.00003;1.94284;1.01437;,
 0.98041;1.50899;0.51980;,
 0.85969;2.00537;0.45829;,
 0.43805;2.00537;0.87993;,
 0.49956;1.50899;1.00065;,
 1.08678;1.50899;-0.15185;,
 0.97688;2.00537;0.02028;,
 0.85969;2.00537;0.45829;,
 0.98041;1.50899;0.51980;,
 1.08678;1.50899;-0.15185;,
 0.85969;2.00537;-0.41774;,
 0.77806;1.50899;-0.75775;,
 0.77806;1.50899;-0.75775;,
 0.43805;2.00537;-0.83938;,
 0.85969;2.00537;-0.41774;,
 0.43805;2.00537;-0.83938;,
 -0.34422;1.50899;-1.03921;,
 -0.43799;2.00537;-0.83938;,
 0.00003;1.94284;-0.97382;,
 -0.77800;1.50899;-0.75775;,
 -0.77800;1.50899;-0.75775;,
 -0.85963;2.00537;-0.41774;,
 -0.43799;2.00537;-0.83938;,
 -1.05894;1.63147;-0.15185;,
 -1.08681;1.33945;0.28064;,
 -0.85963;2.00537;0.45829;,
 -1.05894;1.63147;-0.15185;,
 -0.78853;2.37202;0.07776;,
 -0.85963;2.00537;-0.41774;,
 -0.85963;2.00537;0.45829;,
 -0.51962;2.48972;0.53992;,
 -0.78853;2.37202;0.07776;,
 -0.43799;2.00537;0.87993;,
 -0.43799;2.00537;0.87993;,
 -0.11493;2.48972;0.74612;,
 -0.51962;2.48972;0.53992;,
 0.00003;1.94284;1.01437;,
 0.43805;2.00537;0.87993;,
 0.45087;2.56624;0.49989;,
 -0.11493;2.48972;0.74612;,
 0.85969;2.00537;0.45829;,
 0.45087;2.56624;0.49989;,
 0.43805;2.00537;0.87993;,
 0.75435;2.43331;-0.00582;,
 0.45087;2.56624;0.49989;,
 0.97688;2.00537;0.02028;,
 0.85969;2.00537;0.45829;,
 0.85969;2.00537;-0.41774;,
 0.75435;2.43331;-0.00582;,
 0.85969;2.00537;-0.41774;,
 0.36226;2.44539;-0.62992;,
 0.75435;2.43331;-0.00582;,
 0.43805;2.00537;-0.83938;,
 0.00003;1.94284;-0.97382;,
 -0.11493;2.48972;-0.70557;,
 0.36226;2.44539;-0.62992;,
 0.43805;2.00537;-0.83938;,
 -0.43799;2.00537;-0.83938;,
 -0.43799;2.00537;-0.83938;,
 -0.53518;2.59444;-0.35022;,
 -0.11493;2.48972;-0.70557;,
 -0.85963;2.00537;-0.41774;,
 -0.78853;2.37202;0.07776;,
 -0.53518;2.59444;-0.35022;,
 -0.51962;2.48972;0.53992;,
 -0.25396;2.83589;0.33001;,
 -0.78853;2.37202;0.07776;,
 -0.11493;2.48972;0.74612;,
 -0.25396;2.83589;0.33001;,
 -0.51962;2.48972;0.53992;,
 0.45087;2.56624;0.49989;,
 -0.25396;2.83589;0.33001;,
 -0.11493;2.48972;0.74612;,
 0.75435;2.43331;-0.00582;,
 0.23783;2.86847;-0.01946;,
 0.45087;2.56624;0.49989;,
 0.36226;2.44539;-0.62992;,
 0.23783;2.86847;-0.01946;,
 0.75435;2.43331;-0.00582;,
 -0.11493;2.48972;-0.70557;,
 -0.07737;2.87012;-0.36418;,
 0.36226;2.44539;-0.62992;,
 -0.53518;2.59444;-0.35022;,
 -0.07737;2.87012;-0.36418;,
 -0.11493;2.48972;-0.70557;,
 -0.78853;2.37202;0.07776;,
 -0.25396;2.83589;0.33001;,
 -0.53518;2.59444;-0.35022;,
 0.45087;2.56624;0.49989;,
 0.23783;2.86847;-0.01946;,
 -0.25396;2.83589;0.33001;,
 0.36226;2.44539;-0.62992;,
 -0.07737;2.87012;-0.36418;,
 0.23783;2.86847;-0.01946;,
 -0.07737;2.87012;-0.36418;,
 -0.25396;2.83589;0.33001;,
 0.23783;2.86847;-0.01946;;
 
 116;
 3;0,1,2;,
 3;1,3,4;,
 3;5,6,7;,
 3;8,9,10;,
 3;11,12,13;,
 3;14,15,16;,
 3;17,15,14;,
 3;18,19,20;,
 3;21,22,23;,
 3;24,25,26;,
 3;27,25,24;,
 3;28,29,30;,
 3;31,32,33;,
 3;34,35,36;,
 3;37,38,39;,
 3;32,40,33;,
 3;41,42,43;,
 3;35,44,36;,
 3;45,46,47;,
 3;48,46,45;,
 3;49,50,51;,
 3;52,50,49;,
 3;53,54,55;,
 3;56,57,54;,
 3;58,57,56;,
 3;59,60,61;,
 3;62,60,59;,
 3;38,63,62;,
 3;64,65,66;,
 3;67,68,69;,
 3;67,69,70;,
 3;71,72,73;,
 3;74,72,71;,
 3;75,76,77;,
 3;78,76,75;,
 3;79,80,81;,
 3;82,83,84;,
 3;85,86,87;,
 3;88,89,90;,
 3;91,89,88;,
 3;92,93,94;,
 3;95,96,97;,
 3;98,99,100;,
 3;86,99,98;,
 3;94,101,102;,
 3;103,104,105;,
 3;106,107,108;,
 3;109,110,111;,
 3;112,110,109;,
 3;113,114,115;,
 3;116,114,113;,
 3;117,118,119;,
 3;117,120,121;,
 3;122,123,121;,
 3;124,123,122;,
 3;100,125,126;,
 3;99,125,100;,
 3;127,128,129;,
 3;130,131,128;,
 3;132,131,130;,
 3;102,133,134;,
 3;101,133,102;,
 3;110,135,111;,
 3;129,136,137;,
 3;128,136,129;,
 3;138,139,140;,
 3;141,142,143;,
 3;144,142,141;,
 3;135,145,144;,
 3;146,147,148;,
 3;149,150,151;,
 3;149,151,152;,
 3;153,154,155;,
 3;153,155,156;,
 3;157,158,154;,
 3;159,158,157;,
 3;160,161,162;,
 3;137,161,160;,
 3;136,163,137;,
 3;164,165,166;,
 3;167,165,164;,
 3;168,169,170;,
 3;171,169,168;,
 3;172,173,174;,
 3;174,175,176;,
 3;173,175,174;,
 3;177,178,179;,
 3;180,178,177;,
 3;181,182,183;,
 3;184,182,181;,
 3;185,186,187;,
 3;185,187,184;,
 3;188,189,190;,
 3;188,191,192;,
 3;193,191,194;,
 3;195,196,193;,
 3;197,198,199;,
 3;200,198,197;,
 3;201,202,203;,
 3;201,203,204;,
 3;205,202,201;,
 3;206,207,208;,
 3;209,207,206;,
 3;176,210,211;,
 3;212,213,214;,
 3;215,216,217;,
 3;218,219,220;,
 3;221,222,223;,
 3;224,225,226;,
 3;227,228,229;,
 3;230,231,232;,
 3;233,234,235;,
 3;236,237,238;,
 3;239,240,241;,
 3;234,242,235;,
 3;243,244,242;;
 
 MeshMaterialList {
  2;
  116;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  60;
  -0.080699;-0.958829;-0.272275;,
  0.165174;-0.975943;0.142313;,
  -0.397413;-0.904176;0.156618;,
  -0.269644;-0.764437;0.585601;,
  0.513472;-0.730302;0.450562;,
  0.720541;-0.692789;-0.029394;,
  0.134339;-0.707429;-0.693900;,
  0.496356;-0.755927;-0.426854;,
  -0.329373;-0.744151;-0.581165;,
  0.185678;-0.731480;0.656095;,
  -0.638861;-0.745999;-0.187996;,
  -0.775786;-0.505707;0.377380;,
  -0.026606;-0.394636;0.918452;,
  0.854689;-0.273113;-0.441493;,
  -0.442465;-0.368888;0.817403;,
  0.393526;-0.293697;0.871137;,
  0.775382;-0.437635;0.455256;,
  0.975461;-0.187029;0.116173;,
  0.445399;-0.267021;-0.854587;,
  -0.650216;-0.428870;-0.627128;,
  -0.926034;-0.357074;-0.122308;,
  -0.138976;-0.404926;-0.903726;,
  -0.715883;-0.105751;0.690165;,
  0.762208;-0.074204;0.643065;,
  -0.487294;-0.093801;-0.868185;,
  -0.899675;-0.065642;-0.431596;,
  -0.004001;-0.006096;-0.999973;,
  -0.337196;0.173859;-0.925242;,
  -0.973974;0.004610;0.226613;,
  -0.696985;0.168592;0.696985;,
  -0.200607;0.047986;0.978496;,
  0.019549;0.303439;0.952650;,
  0.413274;0.137771;0.900124;,
  0.860578;0.155884;0.484877;,
  0.984461;0.130713;-0.117260;,
  0.726135;0.121159;-0.676793;,
  0.345141;0.145076;-0.927270;,
  -0.722519;0.164044;-0.671607;,
  -0.963509;0.220852;-0.151242;,
  -0.454442;0.341971;0.822519;,
  0.939893;0.341466;0.001627;,
  0.468432;0.363446;-0.805281;,
  -0.472477;0.381673;-0.794412;,
  -0.815739;0.372337;-0.442646;,
  -0.845341;0.340980;0.411256;,
  0.472774;0.377071;0.796431;,
  0.846200;0.355464;0.396977;,
  0.802693;0.383480;-0.456757;,
  0.024163;0.348886;-0.936854;,
  -0.607080;0.561951;0.561841;,
  -0.057428;0.584283;0.809515;,
  0.785475;0.616742;-0.051558;,
  0.449382;0.607325;-0.655142;,
  -0.155002;0.557586;-0.815520;,
  0.484189;0.697972;0.527632;,
  -0.629506;0.654899;-0.418126;,
  -0.840357;0.539518;0.052152;,
  -0.299454;0.905209;0.301536;,
  -0.069253;0.898022;-0.434465;,
  0.422007;0.905861;-0.036400;;
  116;
  3;0,1,2;,
  3;1,3,2;,
  3;1,9,3;,
  3;1,4,9;,
  3;1,5,4;,
  3;1,7,5;,
  3;0,7,1;,
  3;0,6,7;,
  3;0,8,6;,
  3;0,10,8;,
  3;2,10,0;,
  3;3,11,2;,
  3;2,11,10;,
  3;9,12,3;,
  3;8,21,6;,
  3;11,20,10;,
  3;3,14,11;,
  3;12,14,3;,
  3;9,15,12;,
  3;4,15,9;,
  3;4,16,15;,
  3;5,16,4;,
  3;5,17,16;,
  3;5,13,17;,
  3;7,13,5;,
  3;7,18,13;,
  3;6,18,7;,
  3;21,18,6;,
  3;8,19,21;,
  3;10,20,19;,
  3;10,19,8;,
  3;11,22,28;,
  3;14,22,11;,
  3;14,30,22;,
  3;12,30,14;,
  3;16,23,15;,
  3;16,17,23;,
  3;19,24,21;,
  3;19,25,24;,
  3;20,25,19;,
  3;11,28,20;,
  3;15,30,12;,
  3;21,26,18;,
  3;24,26,21;,
  3;20,28,25;,
  3;22,29,28;,
  3;30,29,22;,
  3;15,32,30;,
  3;23,32,15;,
  3;23,33,32;,
  3;17,33,23;,
  3;17,34,33;,
  3;17,13,34;,
  3;13,35,34;,
  3;18,35,13;,
  3;18,36,35;,
  3;26,36,18;,
  3;24,27,26;,
  3;24,37,27;,
  3;25,37,24;,
  3;25,38,37;,
  3;28,38,25;,
  3;32,31,30;,
  3;26,48,36;,
  3;27,48,26;,
  3;29,44,28;,
  3;29,39,44;,
  3;30,39,29;,
  3;31,39,30;,
  3;32,45,31;,
  3;33,46,45;,
  3;33,45,32;,
  3;34,40,46;,
  3;34,46,33;,
  3;34,47,40;,
  3;35,47,34;,
  3;35,41,47;,
  3;36,41,35;,
  3;48,41,36;,
  3;27,42,48;,
  3;37,42,27;,
  3;37,43,42;,
  3;38,43,37;,
  3;28,44,38;,
  3;38,56,43;,
  3;44,56,38;,
  3;44,49,56;,
  3;39,49,44;,
  3;39,50,49;,
  3;31,50,39;,
  3;45,54,50;,
  3;45,50,31;,
  3;46,54,45;,
  3;46,51,54;,
  3;40,51,46;,
  3;47,51,40;,
  3;47,52,51;,
  3;41,52,47;,
  3;48,53,52;,
  3;48,52,41;,
  3;42,53,48;,
  3;42,55,53;,
  3;43,55,42;,
  3;43,56,55;,
  3;49,57,56;,
  3;50,57,49;,
  3;54,57,50;,
  3;51,59,54;,
  3;52,59,51;,
  3;53,58,52;,
  3;55,58,53;,
  3;56,57,55;,
  3;54,59,57;,
  3;52,58,59;,
  3;57,58,55;,
  3;57,59,58;;
 }
 MeshTextureCoords {
  245;
  0.100000;0.050000;,
  0.100000;0.100000;,
  0.050000;0.100000;,
  0.100000;0.150000;,
  0.050000;0.150000;,
  0.200000;0.100000;,
  0.200000;0.150000;,
  0.150000;0.150000;,
  0.300000;0.100000;,
  0.300000;0.150000;,
  0.250000;0.150000;,
  0.450000;0.100000;,
  0.450000;0.150000;,
  0.400000;0.150000;,
  0.550000;0.100000;,
  0.550000;0.150000;,
  0.500000;0.150000;,
  0.600000;0.100000;,
  0.650000;0.150000;,
  0.650000;0.200000;,
  0.600000;0.200000;,
  0.750000;0.150000;,
  0.750000;0.200000;,
  0.700000;0.200000;,
  0.900000;0.150000;,
  0.900000;0.200000;,
  0.850000;0.200000;,
  0.950000;0.150000;,
  0.100000;0.200000;,
  0.050000;0.250000;,
  0.050000;0.200000;,
  1.000000;0.200000;,
  1.000000;0.250000;,
  0.950000;0.250000;,
  0.200000;0.250000;,
  0.200000;0.300000;,
  0.150000;0.300000;,
  0.750000;0.250000;,
  0.700000;0.300000;,
  0.700000;0.250000;,
  0.950000;0.300000;,
  0.100000;0.300000;,
  0.100000;0.350000;,
  0.050000;0.350000;,
  0.150000;0.350000;,
  0.250000;0.300000;,
  0.250000;0.350000;,
  0.200000;0.350000;,
  0.300000;0.300000;,
  0.350000;0.300000;,
  0.350000;0.350000;,
  0.300000;0.350000;,
  0.400000;0.300000;,
  0.450000;0.300000;,
  0.450000;0.350000;,
  0.400000;0.350000;,
  0.500000;0.300000;,
  0.500000;0.350000;,
  0.550000;0.300000;,
  0.600000;0.300000;,
  0.600000;0.350000;,
  0.550000;0.350000;,
  0.650000;0.300000;,
  0.650000;0.350000;,
  0.800000;0.300000;,
  0.800000;0.350000;,
  0.750000;0.350000;,
  0.900000;0.300000;,
  0.900000;0.350000;,
  0.850000;0.350000;,
  0.850000;0.300000;,
  0.050000;0.400000;,
  0.050000;0.450000;,
  0.000000;0.450000;,
  0.100000;0.400000;,
  0.150000;0.400000;,
  0.150000;0.450000;,
  0.100000;0.450000;,
  0.200000;0.400000;,
  0.350000;0.400000;,
  0.300000;0.450000;,
  0.300000;0.400000;,
  0.400000;0.400000;,
  0.400000;0.450000;,
  0.350000;0.450000;,
  0.800000;0.400000;,
  0.750000;0.450000;,
  0.750000;0.400000;,
  0.850000;0.400000;,
  0.850000;0.450000;,
  0.800000;0.450000;,
  0.900000;0.400000;,
  1.000000;0.400000;,
  1.000000;0.450000;,
  0.950000;0.450000;,
  0.250000;0.450000;,
  0.200000;0.500000;,
  0.200000;0.450000;,
  0.700000;0.450000;,
  0.700000;0.500000;,
  0.650000;0.500000;,
  0.950000;0.500000;,
  0.900000;0.500000;,
  0.050000;0.500000;,
  0.050000;0.550000;,
  0.000000;0.550000;,
  0.150000;0.500000;,
  0.100000;0.550000;,
  0.100000;0.500000;,
  0.250000;0.500000;,
  0.250000;0.550000;,
  0.200000;0.550000;,
  0.300000;0.500000;,
  0.350000;0.500000;,
  0.350000;0.550000;,
  0.300000;0.550000;,
  0.400000;0.500000;,
  0.450000;0.500000;,
  0.450000;0.550000;,
  0.400000;0.550000;,
  0.500000;0.500000;,
  0.500000;0.550000;,
  0.550000;0.500000;,
  0.550000;0.550000;,
  0.600000;0.500000;,
  0.650000;0.550000;,
  0.600000;0.550000;,
  0.750000;0.500000;,
  0.750000;0.550000;,
  0.700000;0.550000;,
  0.800000;0.500000;,
  0.800000;0.550000;,
  0.850000;0.500000;,
  0.900000;0.550000;,
  0.850000;0.550000;,
  0.200000;0.600000;,
  0.700000;0.600000;,
  0.650000;0.600000;,
  0.050000;0.600000;,
  0.000000;0.650000;,
  0.000000;0.600000;,
  0.100000;0.600000;,
  0.100000;0.650000;,
  0.050000;0.650000;,
  0.150000;0.600000;,
  0.150000;0.650000;,
  0.250000;0.600000;,
  0.250000;0.650000;,
  0.200000;0.650000;,
  0.350000;0.600000;,
  0.350000;0.650000;,
  0.300000;0.650000;,
  0.300000;0.600000;,
  0.450000;0.600000;,
  0.450000;0.650000;,
  0.400000;0.650000;,
  0.400000;0.600000;,
  0.500000;0.600000;,
  0.500000;0.650000;,
  0.550000;0.600000;,
  0.600000;0.600000;,
  0.600000;0.650000;,
  0.550000;0.650000;,
  0.650000;0.650000;,
  0.750000;0.600000;,
  0.750000;0.650000;,
  0.700000;0.650000;,
  0.800000;0.600000;,
  0.850000;0.600000;,
  0.850000;0.650000;,
  0.800000;0.650000;,
  0.900000;0.600000;,
  1.000000;0.600000;,
  1.000000;0.650000;,
  0.950000;0.650000;,
  0.950000;0.700000;,
  0.900000;0.700000;,
  0.050000;0.700000;,
  0.050000;0.750000;,
  0.000000;0.750000;,
  0.100000;0.700000;,
  0.150000;0.700000;,
  0.150000;0.750000;,
  0.100000;0.750000;,
  0.200000;0.700000;,
  0.250000;0.700000;,
  0.250000;0.750000;,
  0.200000;0.750000;,
  0.350000;0.700000;,
  0.300000;0.750000;,
  0.300000;0.700000;,
  0.400000;0.750000;,
  0.350000;0.750000;,
  0.450000;0.700000;,
  0.400000;0.700000;,
  0.500000;0.700000;,
  0.450000;0.750000;,
  0.550000;0.700000;,
  0.550000;0.750000;,
  0.500000;0.750000;,
  0.600000;0.700000;,
  0.700000;0.700000;,
  0.700000;0.750000;,
  0.650000;0.750000;,
  0.650000;0.700000;,
  0.750000;0.700000;,
  0.800000;0.700000;,
  0.800000;0.750000;,
  0.750000;0.750000;,
  0.850000;0.700000;,
  0.900000;0.750000;,
  0.850000;0.750000;,
  0.050000;0.800000;,
  0.000000;0.850000;,
  0.000000;0.800000;,
  0.150000;0.800000;,
  0.100000;0.850000;,
  0.100000;0.800000;,
  0.250000;0.800000;,
  0.200000;0.850000;,
  0.200000;0.800000;,
  0.450000;0.800000;,
  0.400000;0.850000;,
  0.400000;0.800000;,
  0.550000;0.800000;,
  0.500000;0.850000;,
  0.500000;0.800000;,
  0.700000;0.800000;,
  0.650000;0.850000;,
  0.650000;0.800000;,
  0.800000;0.800000;,
  0.750000;0.850000;,
  0.750000;0.800000;,
  0.950000;0.800000;,
  0.950000;0.850000;,
  0.900000;0.850000;,
  0.350000;0.850000;,
  0.350000;0.900000;,
  0.300000;0.900000;,
  0.600000;0.850000;,
  0.600000;0.900000;,
  0.550000;0.900000;,
  0.900000;0.900000;,
  0.950000;0.900000;,
  0.900000;0.950000;;
 }
}