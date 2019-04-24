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
 274;
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 0.00000;9.00000;0.00000;,
 1.31802;8.31492;-3.18198;,
 0.00000;8.31492;-3.44415;,
 2.43538;8.31492;-2.43538;,
 3.18198;8.31492;-1.31802;,
 3.44415;8.31492;0.00000;,
 3.18198;8.31492;1.31802;,
 2.43538;8.31492;2.43538;,
 1.31802;8.31492;3.18198;,
 0.00000;8.31492;3.44415;,
 -1.31802;8.31492;3.18198;,
 -2.43538;8.31492;2.43538;,
 -3.18198;8.31492;1.31802;,
 -3.44415;8.31492;-0.00000;,
 -3.18198;8.31492;-1.31802;,
 -2.43538;8.31492;-2.43538;,
 -1.31802;8.31492;-3.18198;,
 2.43538;6.36396;-5.87953;,
 0.00000;6.36396;-6.36396;,
 4.50000;6.36396;-4.50000;,
 5.87953;6.36396;-2.43538;,
 6.36396;6.36396;0.00000;,
 5.87953;6.36396;2.43538;,
 4.50000;6.36396;4.50000;,
 2.43538;6.36396;5.87953;,
 0.00000;6.36396;6.36396;,
 -2.43538;6.36396;5.87953;,
 -4.50000;6.36396;4.50000;,
 -5.87953;6.36396;2.43538;,
 -6.36396;6.36396;-0.00000;,
 -5.87953;6.36396;-2.43538;,
 -4.50000;6.36396;-4.50000;,
 -2.43538;6.36396;-5.87953;,
 3.18198;3.44415;-7.68198;,
 0.00000;3.44415;-8.31492;,
 5.87953;3.44415;-5.87953;,
 7.68198;3.44415;-3.18198;,
 8.31492;3.44415;0.00000;,
 7.68198;3.44415;3.18198;,
 5.87953;3.44415;5.87953;,
 3.18198;3.44415;7.68198;,
 0.00000;3.44415;8.31492;,
 -3.18198;3.44415;7.68198;,
 -5.87953;3.44415;5.87953;,
 -7.68198;3.44415;3.18198;,
 -8.31492;3.44415;-0.00000;,
 -7.68198;3.44415;-3.18198;,
 -5.87953;3.44415;-5.87953;,
 -3.18198;3.44415;-7.68198;,
 3.44415;0.00000;-8.31492;,
 0.00000;0.00000;-9.00000;,
 6.36396;0.00000;-6.36396;,
 8.31492;0.00000;-3.44415;,
 9.00000;0.00000;0.00000;,
 8.31492;0.00000;3.44415;,
 6.36396;0.00000;6.36396;,
 3.44415;0.00000;8.31492;,
 0.00000;0.00000;9.00000;,
 -3.44415;0.00000;8.31492;,
 -6.36396;0.00000;6.36396;,
 -8.31492;0.00000;3.44415;,
 -9.00000;0.00000;-0.00000;,
 -8.31492;0.00000;-3.44415;,
 -6.36396;0.00000;-6.36396;,
 -3.44415;0.00000;-8.31492;,
 3.44415;-22.75000;-8.31492;,
 0.00000;-22.75000;-9.00000;,
 6.36396;-22.75000;-6.36396;,
 8.31492;-22.75000;-3.44415;,
 9.00000;-22.75000;0.00000;,
 8.31492;-22.75000;3.44415;,
 6.36396;-22.75000;6.36396;,
 3.44415;-22.75000;8.31492;,
 0.00000;-22.75000;9.00000;,
 -3.44415;-22.75000;8.31492;,
 -6.36396;-22.75000;6.36396;,
 -8.31492;-22.75000;3.44415;,
 -9.00000;-22.75000;-0.00000;,
 -8.31492;-22.75000;-3.44415;,
 -6.36396;-22.75000;-6.36396;,
 -3.44415;-22.75000;-8.31492;,
 3.44415;-45.50000;-8.31492;,
 0.00000;-45.50000;-9.00000;,
 6.36396;-45.50000;-6.36396;,
 8.31492;-45.50000;-3.44415;,
 9.00000;-45.50000;0.00000;,
 8.31492;-45.50000;3.44415;,
 6.36396;-45.50000;6.36396;,
 3.44415;-45.50000;8.31492;,
 0.00000;-45.50000;9.00000;,
 -3.44415;-45.50000;8.31492;,
 -6.36396;-45.50000;6.36396;,
 -8.31492;-45.50000;3.44415;,
 -9.00000;-45.50000;-0.00000;,
 -8.31492;-45.50000;-3.44415;,
 -6.36396;-45.50000;-6.36396;,
 -3.44415;-45.50000;-8.31492;,
 3.44415;-68.25000;-8.31492;,
 0.00000;-68.25000;-9.00000;,
 6.36396;-68.25000;-6.36396;,
 8.31492;-68.25000;-3.44415;,
 9.00000;-68.25000;0.00000;,
 8.31492;-68.25000;3.44415;,
 6.36396;-68.25000;6.36396;,
 3.44415;-68.25000;8.31492;,
 0.00000;-68.25000;9.00000;,
 -3.44415;-68.25000;8.31492;,
 -6.36396;-68.25000;6.36396;,
 -8.31492;-68.25000;3.44415;,
 -9.00000;-68.25000;-0.00000;,
 -8.31492;-68.25000;-3.44415;,
 -6.36396;-68.25000;-6.36396;,
 -3.44415;-68.25000;-8.31492;,
 3.44415;-91.00000;-8.31492;,
 0.00000;-91.00000;-9.00000;,
 6.36396;-91.00000;-6.36396;,
 8.31492;-91.00000;-3.44415;,
 9.00000;-91.00000;0.00000;,
 8.31492;-91.00000;3.44415;,
 6.36396;-91.00000;6.36396;,
 3.44415;-91.00000;8.31492;,
 0.00000;-91.00000;9.00000;,
 -3.44415;-91.00000;8.31492;,
 -6.36396;-91.00000;6.36396;,
 -8.31492;-91.00000;3.44415;,
 -9.00000;-91.00000;-0.00000;,
 -8.31492;-91.00000;-3.44415;,
 -6.36396;-91.00000;-6.36396;,
 -3.44415;-91.00000;-8.31492;,
 3.44415;-113.75000;-8.31492;,
 0.00000;-113.75000;-9.00000;,
 6.36396;-113.75000;-6.36396;,
 8.31492;-113.75000;-3.44415;,
 9.00000;-113.75000;0.00000;,
 8.31492;-113.75000;3.44415;,
 6.36396;-113.75000;6.36396;,
 3.44415;-113.75000;8.31492;,
 0.00000;-113.75000;9.00000;,
 -3.44415;-113.75000;8.31492;,
 -6.36396;-113.75000;6.36396;,
 -8.31492;-113.75000;3.44415;,
 -9.00000;-113.75000;-0.00000;,
 -8.31492;-113.75000;-3.44415;,
 -6.36396;-113.75000;-6.36396;,
 -3.44415;-113.75000;-8.31492;,
 3.44415;-136.50000;-8.31492;,
 0.00000;-136.50000;-9.00000;,
 6.36396;-136.50000;-6.36396;,
 8.31492;-136.50000;-3.44415;,
 9.00000;-136.50000;0.00000;,
 8.31492;-136.50000;3.44415;,
 6.36396;-136.50000;6.36396;,
 3.44415;-136.50000;8.31492;,
 0.00000;-136.50000;9.00000;,
 -3.44415;-136.50000;8.31492;,
 -6.36396;-136.50000;6.36396;,
 -8.31492;-136.50000;3.44415;,
 -9.00000;-136.50000;-0.00000;,
 -8.31492;-136.50000;-3.44415;,
 -6.36396;-136.50000;-6.36396;,
 -3.44415;-136.50000;-8.31492;,
 3.44415;-159.25000;-8.31492;,
 0.00000;-159.25000;-9.00000;,
 6.36396;-159.25000;-6.36396;,
 8.31492;-159.25000;-3.44415;,
 9.00000;-159.25000;0.00000;,
 8.31492;-159.25000;3.44415;,
 6.36396;-159.25000;6.36396;,
 3.44415;-159.25000;8.31492;,
 0.00000;-159.25000;9.00000;,
 -3.44415;-159.25000;8.31492;,
 -6.36396;-159.25000;6.36396;,
 -8.31492;-159.25000;3.44415;,
 -9.00000;-159.25000;-0.00000;,
 -8.31492;-159.25000;-3.44415;,
 -6.36396;-159.25000;-6.36396;,
 -3.44415;-159.25000;-8.31492;,
 3.44415;-182.00000;-8.31492;,
 0.00000;-182.00000;-9.00000;,
 6.36396;-182.00000;-6.36396;,
 8.31492;-182.00000;-3.44415;,
 9.00000;-182.00000;0.00000;,
 8.31492;-182.00000;3.44415;,
 6.36396;-182.00000;6.36396;,
 3.44415;-182.00000;8.31492;,
 0.00000;-182.00000;9.00000;,
 -3.44415;-182.00000;8.31492;,
 -6.36396;-182.00000;6.36396;,
 -8.31492;-182.00000;3.44415;,
 -9.00000;-182.00000;-0.00000;,
 -8.31492;-182.00000;-3.44415;,
 -6.36396;-182.00000;-6.36396;,
 -3.44415;-182.00000;-8.31492;,
 3.18198;-185.44416;-7.68198;,
 0.00000;-185.44416;-8.31492;,
 5.87953;-185.44416;-5.87953;,
 7.68198;-185.44416;-3.18198;,
 8.31492;-185.44416;0.00000;,
 7.68198;-185.44416;3.18198;,
 5.87953;-185.44416;5.87953;,
 3.18198;-185.44416;7.68198;,
 0.00000;-185.44416;8.31492;,
 -3.18198;-185.44416;7.68198;,
 -5.87953;-185.44416;5.87953;,
 -7.68198;-185.44416;3.18198;,
 -8.31492;-185.44416;-0.00000;,
 -7.68198;-185.44416;-3.18198;,
 -5.87953;-185.44416;-5.87953;,
 -3.18198;-185.44416;-7.68198;,
 2.43538;-188.36397;-5.87953;,
 0.00000;-188.36397;-6.36396;,
 4.50000;-188.36397;-4.50000;,
 5.87953;-188.36397;-2.43538;,
 6.36396;-188.36397;0.00000;,
 5.87953;-188.36397;2.43538;,
 4.50000;-188.36397;4.50000;,
 2.43538;-188.36397;5.87953;,
 0.00000;-188.36397;6.36396;,
 -2.43538;-188.36397;5.87953;,
 -4.50000;-188.36397;4.50000;,
 -5.87953;-188.36397;2.43538;,
 -6.36396;-188.36397;-0.00000;,
 -5.87953;-188.36397;-2.43538;,
 -4.50000;-188.36397;-4.50000;,
 -2.43538;-188.36397;-5.87953;,
 1.31802;-190.31492;-3.18198;,
 0.00000;-190.31492;-3.44415;,
 2.43538;-190.31492;-2.43538;,
 3.18198;-190.31492;-1.31802;,
 3.44415;-190.31492;0.00000;,
 3.18198;-190.31492;1.31802;,
 2.43538;-190.31492;2.43538;,
 1.31802;-190.31492;3.18198;,
 0.00000;-190.31492;3.44415;,
 -1.31802;-190.31492;3.18198;,
 -2.43538;-190.31492;2.43538;,
 -3.18198;-190.31492;1.31802;,
 -3.44415;-190.31492;-0.00000;,
 -3.18198;-190.31492;-1.31802;,
 -2.43538;-190.31492;-2.43538;,
 -1.31802;-190.31492;-3.18198;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;,
 0.00000;-191.00000;-0.00000;;
 
 288;
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
 3;0,2,16;,
 4;2,1,17,18;,
 4;1,3,19,17;,
 4;3,4,20,19;,
 4;4,5,21,20;,
 4;5,6,22,21;,
 4;6,7,23,22;,
 4;7,8,24,23;,
 4;8,9,25,24;,
 4;9,10,26,25;,
 4;10,11,27,26;,
 4;11,12,28,27;,
 4;12,13,29,28;,
 4;13,14,30,29;,
 4;14,15,31,30;,
 4;15,16,32,31;,
 4;16,2,18,32;,
 4;18,17,33,34;,
 4;17,19,35,33;,
 4;19,20,36,35;,
 4;20,21,37,36;,
 4;21,22,38,37;,
 4;22,23,39,38;,
 4;23,24,40,39;,
 4;24,25,41,40;,
 4;25,26,42,41;,
 4;26,27,43,42;,
 4;27,28,44,43;,
 4;28,29,45,44;,
 4;29,30,46,45;,
 4;30,31,47,46;,
 4;31,32,48,47;,
 4;32,18,34,48;,
 4;34,33,49,50;,
 4;33,35,51,49;,
 4;35,36,52,51;,
 4;36,37,53,52;,
 4;37,38,54,53;,
 4;38,39,55,54;,
 4;39,40,56,55;,
 4;40,41,57,56;,
 4;41,42,58,57;,
 4;42,43,59,58;,
 4;43,44,60,59;,
 4;44,45,61,60;,
 4;45,46,62,61;,
 4;46,47,63,62;,
 4;47,48,64,63;,
 4;48,34,50,64;,
 4;50,49,65,66;,
 4;49,51,67,65;,
 4;51,52,68,67;,
 4;52,53,69,68;,
 4;53,54,70,69;,
 4;54,55,71,70;,
 4;55,56,72,71;,
 4;56,57,73,72;,
 4;57,58,74,73;,
 4;58,59,75,74;,
 4;59,60,76,75;,
 4;60,61,77,76;,
 4;61,62,78,77;,
 4;62,63,79,78;,
 4;63,64,80,79;,
 4;64,50,66,80;,
 4;66,65,81,82;,
 4;65,67,83,81;,
 4;67,68,84,83;,
 4;68,69,85,84;,
 4;69,70,86,85;,
 4;70,71,87,86;,
 4;71,72,88,87;,
 4;72,73,89,88;,
 4;73,74,90,89;,
 4;74,75,91,90;,
 4;75,76,92,91;,
 4;76,77,93,92;,
 4;77,78,94,93;,
 4;78,79,95,94;,
 4;79,80,96,95;,
 4;80,66,82,96;,
 4;82,81,97,98;,
 4;81,83,99,97;,
 4;83,84,100,99;,
 4;84,85,101,100;,
 4;85,86,102,101;,
 4;86,87,103,102;,
 4;87,88,104,103;,
 4;88,89,105,104;,
 4;89,90,106,105;,
 4;90,91,107,106;,
 4;91,92,108,107;,
 4;92,93,109,108;,
 4;93,94,110,109;,
 4;94,95,111,110;,
 4;95,96,112,111;,
 4;96,82,98,112;,
 4;98,97,113,114;,
 4;97,99,115,113;,
 4;99,100,116,115;,
 4;100,101,117,116;,
 4;101,102,118,117;,
 4;102,103,119,118;,
 4;103,104,120,119;,
 4;104,105,121,120;,
 4;105,106,122,121;,
 4;106,107,123,122;,
 4;107,108,124,123;,
 4;108,109,125,124;,
 4;109,110,126,125;,
 4;110,111,127,126;,
 4;111,112,128,127;,
 4;112,98,114,128;,
 4;114,113,129,130;,
 4;113,115,131,129;,
 4;115,116,132,131;,
 4;116,117,133,132;,
 4;117,118,134,133;,
 4;118,119,135,134;,
 4;119,120,136,135;,
 4;120,121,137,136;,
 4;121,122,138,137;,
 4;122,123,139,138;,
 4;123,124,140,139;,
 4;124,125,141,140;,
 4;125,126,142,141;,
 4;126,127,143,142;,
 4;127,128,144,143;,
 4;128,114,130,144;,
 4;130,129,145,146;,
 4;129,131,147,145;,
 4;131,132,148,147;,
 4;132,133,149,148;,
 4;133,134,150,149;,
 4;134,135,151,150;,
 4;135,136,152,151;,
 4;136,137,153,152;,
 4;137,138,154,153;,
 4;138,139,155,154;,
 4;139,140,156,155;,
 4;140,141,157,156;,
 4;141,142,158,157;,
 4;142,143,159,158;,
 4;143,144,160,159;,
 4;144,130,146,160;,
 4;146,145,161,162;,
 4;145,147,163,161;,
 4;147,148,164,163;,
 4;148,149,165,164;,
 4;149,150,166,165;,
 4;150,151,167,166;,
 4;151,152,168,167;,
 4;152,153,169,168;,
 4;153,154,170,169;,
 4;154,155,171,170;,
 4;155,156,172,171;,
 4;156,157,173,172;,
 4;157,158,174,173;,
 4;158,159,175,174;,
 4;159,160,176,175;,
 4;160,146,162,176;,
 4;162,161,177,178;,
 4;161,163,179,177;,
 4;163,164,180,179;,
 4;164,165,181,180;,
 4;165,166,182,181;,
 4;166,167,183,182;,
 4;167,168,184,183;,
 4;168,169,185,184;,
 4;169,170,186,185;,
 4;170,171,187,186;,
 4;171,172,188,187;,
 4;172,173,189,188;,
 4;173,174,190,189;,
 4;174,175,191,190;,
 4;175,176,192,191;,
 4;176,162,178,192;,
 4;178,177,193,194;,
 4;177,179,195,193;,
 4;179,180,196,195;,
 4;180,181,197,196;,
 4;181,182,198,197;,
 4;182,183,199,198;,
 4;183,184,200,199;,
 4;184,185,201,200;,
 4;185,186,202,201;,
 4;186,187,203,202;,
 4;187,188,204,203;,
 4;188,189,205,204;,
 4;189,190,206,205;,
 4;190,191,207,206;,
 4;191,192,208,207;,
 4;192,178,194,208;,
 4;194,193,209,210;,
 4;193,195,211,209;,
 4;195,196,212,211;,
 4;196,197,213,212;,
 4;197,198,214,213;,
 4;198,199,215,214;,
 4;199,200,216,215;,
 4;200,201,217,216;,
 4;201,202,218,217;,
 4;202,203,219,218;,
 4;203,204,220,219;,
 4;204,205,221,220;,
 4;205,206,222,221;,
 4;206,207,223,222;,
 4;207,208,224,223;,
 4;208,194,210,224;,
 4;210,209,225,226;,
 4;209,211,227,225;,
 4;211,212,228,227;,
 4;212,213,229,228;,
 4;213,214,230,229;,
 4;214,215,231,230;,
 4;215,216,232,231;,
 4;216,217,233,232;,
 4;217,218,234,233;,
 4;218,219,235,234;,
 4;219,220,236,235;,
 4;220,221,237,236;,
 4;221,222,238,237;,
 4;222,223,239,238;,
 4;223,224,240,239;,
 4;224,210,226,240;,
 4;226,225,241,242;,
 4;225,227,243,241;,
 4;227,228,244,243;,
 4;228,229,245,244;,
 4;229,230,246,245;,
 4;230,231,247,246;,
 4;231,232,248,247;,
 4;232,233,249,248;,
 4;233,234,250,249;,
 4;234,235,251,250;,
 4;235,236,252,251;,
 4;236,237,253,252;,
 4;237,238,254,253;,
 4;238,239,255,254;,
 4;239,240,256,255;,
 4;240,226,242,256;,
 4;242,241,257,258;,
 4;241,243,259,257;,
 4;243,244,260,259;,
 4;244,245,261,260;,
 4;245,246,262,261;,
 4;246,247,263,262;,
 4;247,248,264,263;,
 4;248,249,265,264;,
 4;249,250,266,265;,
 4;250,251,267,266;,
 4;251,252,268,267;,
 4;252,253,269,268;,
 4;253,254,270,269;,
 4;254,255,271,270;,
 4;255,256,272,271;,
 4;256,242,258,272;,
 3;258,257,273;,
 3;257,259,273;,
 3;259,260,273;,
 3;260,261,273;,
 3;261,262,273;,
 3;262,263,273;,
 3;263,264,273;,
 3;264,265,273;,
 3;265,266,273;,
 3;266,267,273;,
 3;267,268,273;,
 3;268,269,273;,
 3;269,270,273;,
 3;270,271,273;,
 3;271,272,273;,
 3;272,258,273;;
 
 MeshMaterialList {
  1;
  288;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  177;
  0.000000;0.000000;0.000000;,
  0.000000;0.924082;-0.382195;,
  0.146260;0.924082;-0.353102;,
  0.270253;0.924082;-0.270253;,
  0.353102;0.924082;-0.146260;,
  0.382195;0.924082;0.000000;,
  0.353102;0.924082;0.146260;,
  0.270253;0.924082;0.270253;,
  0.146260;0.924082;0.353102;,
  0.000000;0.924082;0.382195;,
  -0.146260;0.924082;0.353102;,
  -0.270253;0.924082;0.270253;,
  -0.353102;0.924082;0.146260;,
  -0.382195;0.924082;-0.000000;,
  -0.353102;0.924082;-0.146260;,
  -0.270253;0.924082;-0.270253;,
  -0.146260;0.924082;-0.353102;,
  0.000000;0.707629;-0.706585;,
  0.270398;0.707629;-0.652799;,
  0.499631;0.707629;-0.499631;,
  0.652799;0.707629;-0.270398;,
  0.706585;0.707629;0.000000;,
  0.652799;0.707629;0.270398;,
  0.499631;0.707629;0.499631;,
  0.270398;0.707629;0.652799;,
  0.000000;0.707629;0.706585;,
  -0.270398;0.707629;0.652799;,
  -0.499631;0.707629;0.499631;,
  -0.652799;0.707629;0.270398;,
  -0.706585;0.707629;-0.000000;,
  -0.652799;0.707629;-0.270398;,
  -0.499631;0.707629;-0.499631;,
  -0.270398;0.707629;-0.652799;,
  0.000000;0.383160;-0.923682;,
  0.353478;0.383160;-0.853371;,
  0.653142;0.383160;-0.653142;,
  0.853371;0.383160;-0.353478;,
  0.923682;0.383160;0.000000;,
  0.853371;0.383160;0.353478;,
  0.653142;0.383160;0.653142;,
  0.353478;0.383160;0.853371;,
  0.000000;0.383160;0.923682;,
  -0.353478;0.383160;0.853371;,
  -0.653142;0.383160;0.653142;,
  -0.853371;0.383160;0.353478;,
  -0.923682;0.383160;0.000000;,
  -0.853371;0.383160;-0.353478;,
  -0.653142;0.383160;-0.653142;,
  -0.353477;0.383160;-0.853371;,
  0.000000;0.098053;-0.995181;,
  0.380839;0.098053;-0.919428;,
  0.703699;0.098053;-0.703699;,
  0.919428;0.098053;-0.380839;,
  0.995181;0.098053;0.000000;,
  0.919428;0.098053;0.380839;,
  0.703699;0.098053;0.703699;,
  0.380839;0.098053;0.919428;,
  0.000000;0.098053;0.995181;,
  -0.380839;0.098053;0.919428;,
  -0.703699;0.098053;0.703700;,
  -0.919427;0.098053;0.380839;,
  -0.995181;0.098053;0.000000;,
  -0.919427;0.098053;-0.380840;,
  -0.703699;0.098053;-0.703700;,
  -0.380839;0.098053;-0.919428;,
  0.000000;0.000000;-1.000000;,
  0.382683;0.000000;-0.923880;,
  0.707107;0.000000;-0.707107;,
  0.923880;0.000000;-0.382683;,
  1.000000;0.000000;0.000000;,
  0.923880;0.000000;0.382683;,
  0.707107;0.000000;0.707107;,
  0.382683;0.000000;0.923880;,
  0.000000;0.000000;1.000000;,
  -0.382683;0.000000;0.923880;,
  -0.707107;0.000000;0.707107;,
  -0.923879;0.000000;0.382684;,
  -1.000000;0.000000;0.000000;,
  -0.923879;0.000000;-0.382684;,
  -0.707107;0.000000;-0.707107;,
  -0.382683;0.000000;-0.923880;,
  0.000000;-0.098053;-0.995181;,
  0.380839;-0.098053;-0.919428;,
  0.703699;-0.098053;-0.703699;,
  0.919428;-0.098053;-0.380839;,
  0.995181;-0.098053;-0.000000;,
  0.919428;-0.098053;0.380839;,
  0.703699;-0.098053;0.703699;,
  0.380839;-0.098053;0.919428;,
  0.000000;-0.098053;0.995181;,
  -0.380839;-0.098053;0.919428;,
  -0.703699;-0.098053;0.703700;,
  -0.919427;-0.098053;0.380839;,
  -0.995181;-0.098053;0.000000;,
  -0.919427;-0.098053;-0.380840;,
  -0.703699;-0.098053;-0.703700;,
  -0.380839;-0.098053;-0.919428;,
  0.000000;-0.383159;-0.923682;,
  0.353478;-0.383159;-0.853371;,
  0.653142;-0.383159;-0.653142;,
  0.853371;-0.383159;-0.353478;,
  0.923682;-0.383160;0.000000;,
  0.853371;-0.383160;0.353478;,
  0.653142;-0.383159;0.653142;,
  0.353478;-0.383159;0.853371;,
  0.000000;-0.383160;0.923682;,
  -0.353478;-0.383159;0.853371;,
  -0.653142;-0.383160;0.653142;,
  -0.853371;-0.383160;0.353478;,
  -0.923682;-0.383160;0.000000;,
  -0.853371;-0.383160;-0.353478;,
  -0.653142;-0.383160;-0.653142;,
  -0.353478;-0.383160;-0.853371;,
  0.000000;-0.707629;-0.706584;,
  0.270398;-0.707629;-0.652799;,
  0.499631;-0.707629;-0.499631;,
  0.652799;-0.707629;-0.270398;,
  0.706584;-0.707629;0.000000;,
  0.652799;-0.707629;0.270398;,
  0.499631;-0.707629;0.499631;,
  0.270398;-0.707629;0.652799;,
  0.000000;-0.707629;0.706584;,
  -0.270398;-0.707629;0.652799;,
  -0.499631;-0.707629;0.499631;,
  -0.652799;-0.707629;0.270398;,
  -0.706584;-0.707629;-0.000000;,
  -0.652799;-0.707629;-0.270398;,
  -0.499630;-0.707629;-0.499631;,
  -0.270398;-0.707629;-0.652799;,
  0.000000;-0.924082;-0.382194;,
  0.146259;-0.924082;-0.353102;,
  0.270252;-0.924082;-0.270252;,
  0.353102;-0.924082;-0.146259;,
  0.382194;-0.924082;0.000000;,
  0.353102;-0.924082;0.146259;,
  0.270252;-0.924082;0.270252;,
  0.146260;-0.924082;0.353102;,
  0.000000;-0.924082;0.382194;,
  -0.146259;-0.924082;0.353102;,
  -0.270252;-0.924082;0.270252;,
  -0.353102;-0.924082;0.146260;,
  -0.382194;-0.924082;-0.000000;,
  -0.353102;-0.924082;-0.146260;,
  -0.270252;-0.924082;-0.270252;,
  -0.146259;-0.924082;-0.353102;,
  0.000000;-0.980785;-0.195090;,
  0.074658;-0.980785;-0.180240;,
  0.137949;-0.980785;-0.137949;,
  0.180240;-0.980785;-0.074658;,
  0.195090;-0.980785;-0.000000;,
  0.180240;-0.980785;0.074658;,
  0.137949;-0.980785;0.137949;,
  0.074658;-0.980785;0.180240;,
  0.000000;-0.980785;0.195090;,
  -0.074658;-0.980785;0.180240;,
  -0.137949;-0.980785;0.137949;,
  -0.180240;-0.980785;0.074658;,
  -0.195090;-0.980785;0.000000;,
  -0.180240;-0.980785;-0.074658;,
  -0.137949;-0.980785;-0.137949;,
  -0.074658;-0.980785;-0.180240;,
  0.000000;0.980785;-0.195090;,
  0.074658;0.980785;-0.180240;,
  0.137949;0.980785;-0.137949;,
  0.180240;0.980785;-0.074658;,
  0.195090;0.980785;0.000000;,
  0.180240;0.980785;0.074658;,
  0.137949;0.980785;0.137949;,
  0.074658;0.980785;0.180240;,
  0.000000;0.980785;0.195090;,
  -0.074658;0.980785;0.180240;,
  -0.137949;0.980785;0.137949;,
  -0.180240;0.980785;0.074658;,
  -0.195090;0.980785;0.000000;,
  -0.180240;0.980785;-0.074658;,
  -0.137949;0.980785;-0.137949;,
  -0.074658;0.980785;-0.180240;;
  288;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;161,162,2,1;,
  4;162,163,3,2;,
  4;163,164,4,3;,
  4;164,165,5,4;,
  4;165,166,6,5;,
  4;166,167,7,6;,
  4;167,168,8,7;,
  4;168,169,9,8;,
  4;169,170,10,9;,
  4;170,171,11,10;,
  4;171,172,12,11;,
  4;172,173,13,12;,
  4;173,174,14,13;,
  4;174,175,15,14;,
  4;175,176,16,15;,
  4;176,161,1,16;,
  4;1,2,18,17;,
  4;2,3,19,18;,
  4;3,4,20,19;,
  4;4,5,21,20;,
  4;5,6,22,21;,
  4;6,7,23,22;,
  4;7,8,24,23;,
  4;8,9,25,24;,
  4;9,10,26,25;,
  4;10,11,27,26;,
  4;11,12,28,27;,
  4;12,13,29,28;,
  4;13,14,30,29;,
  4;14,15,31,30;,
  4;15,16,32,31;,
  4;16,1,17,32;,
  4;17,18,34,33;,
  4;18,19,35,34;,
  4;19,20,36,35;,
  4;20,21,37,36;,
  4;21,22,38,37;,
  4;22,23,39,38;,
  4;23,24,40,39;,
  4;24,25,41,40;,
  4;25,26,42,41;,
  4;26,27,43,42;,
  4;27,28,44,43;,
  4;28,29,45,44;,
  4;29,30,46,45;,
  4;30,31,47,46;,
  4;31,32,48,47;,
  4;32,17,33,48;,
  4;33,34,50,49;,
  4;34,35,51,50;,
  4;35,36,52,51;,
  4;36,37,53,52;,
  4;37,38,54,53;,
  4;38,39,55,54;,
  4;39,40,56,55;,
  4;40,41,57,56;,
  4;41,42,58,57;,
  4;42,43,59,58;,
  4;43,44,60,59;,
  4;44,45,61,60;,
  4;45,46,62,61;,
  4;46,47,63,62;,
  4;47,48,64,63;,
  4;48,33,49,64;,
  4;49,50,66,65;,
  4;50,51,67,66;,
  4;51,52,68,67;,
  4;52,53,69,68;,
  4;53,54,70,69;,
  4;54,55,71,70;,
  4;55,56,72,71;,
  4;56,57,73,72;,
  4;57,58,74,73;,
  4;58,59,75,74;,
  4;59,60,76,75;,
  4;60,61,77,76;,
  4;61,62,78,77;,
  4;62,63,79,78;,
  4;63,64,80,79;,
  4;64,49,65,80;,
  4;65,66,66,65;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,65,65,80;,
  4;65,66,66,65;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,65,65,80;,
  4;65,66,66,65;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,65,65,80;,
  4;65,66,66,65;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,65,65,80;,
  4;65,66,66,65;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,65,65,80;,
  4;65,66,66,65;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,65,65,80;,
  4;65,66,82,81;,
  4;66,67,83,82;,
  4;67,68,84,83;,
  4;68,69,85,84;,
  4;69,70,86,85;,
  4;70,71,87,86;,
  4;71,72,88,87;,
  4;72,73,89,88;,
  4;73,74,90,89;,
  4;74,75,91,90;,
  4;75,76,92,91;,
  4;76,77,93,92;,
  4;77,78,94,93;,
  4;78,79,95,94;,
  4;79,80,96,95;,
  4;80,65,81,96;,
  4;81,82,98,97;,
  4;82,83,99,98;,
  4;83,84,100,99;,
  4;84,85,101,100;,
  4;85,86,102,101;,
  4;86,87,103,102;,
  4;87,88,104,103;,
  4;88,89,105,104;,
  4;89,90,106,105;,
  4;90,91,107,106;,
  4;91,92,108,107;,
  4;92,93,109,108;,
  4;93,94,110,109;,
  4;94,95,111,110;,
  4;95,96,112,111;,
  4;96,81,97,112;,
  4;97,98,114,113;,
  4;98,99,115,114;,
  4;99,100,116,115;,
  4;100,101,117,116;,
  4;101,102,118,117;,
  4;102,103,119,118;,
  4;103,104,120,119;,
  4;104,105,121,120;,
  4;105,106,122,121;,
  4;106,107,123,122;,
  4;107,108,124,123;,
  4;108,109,125,124;,
  4;109,110,126,125;,
  4;110,111,127,126;,
  4;111,112,128,127;,
  4;112,97,113,128;,
  4;113,114,130,129;,
  4;114,115,131,130;,
  4;115,116,132,131;,
  4;116,117,133,132;,
  4;117,118,134,133;,
  4;118,119,135,134;,
  4;119,120,136,135;,
  4;120,121,137,136;,
  4;121,122,138,137;,
  4;122,123,139,138;,
  4;123,124,140,139;,
  4;124,125,141,140;,
  4;125,126,142,141;,
  4;126,127,143,142;,
  4;127,128,144,143;,
  4;128,113,129,144;,
  4;129,130,146,145;,
  4;130,131,147,146;,
  4;131,132,148,147;,
  4;132,133,149,148;,
  4;133,134,150,149;,
  4;134,135,151,150;,
  4;135,136,152,151;,
  4;136,137,153,152;,
  4;137,138,154,153;,
  4;138,139,155,154;,
  4;139,140,156,155;,
  4;140,141,157,156;,
  4;141,142,158,157;,
  4;142,143,159,158;,
  4;143,144,160,159;,
  4;144,129,145,160;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;;
 }
 MeshTextureCoords {
  274;
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
