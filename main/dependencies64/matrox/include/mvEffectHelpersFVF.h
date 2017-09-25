// $Archive: /VP/FLEXVIDEO/LIBS/mvEffectHelpers/inc/mvEffectHelpersFVF.h $

//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2004. All rights reserved. 
//
// This code and information is provided "as is" without warranty of any kind, 
// either expressed or implied, including but not limited to the implied 
// warranties of merchantability and/or fitness for a particular purpose.
//
// Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
// changes in specifications and code at any time and without notice. 
// No responsibility is assumed by Matrox Electronic Systems Ltd. for 
// its use; nor for any infringements of patents or other rights of 
// third parties resulting from its use. No license is granted under 
// any patents or patent rights of Matrox Electronic Systems Ltd.
//
//-------------------------------------------------------------------------------
//	created:	   2004/5/7       7:19
//	filename: 	mvEffectHelpersFVF.h
//	author:		
//===============================================================================


#ifndef _MVEFFECTHELPERSFVF_5E0426B6_5170_4dc8_B746_D47B1D562FAB_
#define _MVEFFECTHELPERSFVF_5E0426B6_5170_4dc8_B746_D47B1D562FAB_

#pragma once

namespace NMvEffectHelpers
{
   //
   // Position only
   //
   struct SMvVertex_XYZ
   {
      float fx;
      float fy;
      float fz;
   };

   const unsigned long g_kulFVF_XYZ = (keMvFVF_XYZ);

   const SMvVertexElement g_kasDeclaration_XYZ[] = 
   {
      {0, 0,  keMvDeclTypeFloat3, keMvDeclMethodDefault, keMvDeclUsagePosition, 0},
      keMvDeclEnd() 
   };


   //
   // Position and diffuse
   //
   struct SMvVertex_XYZDiff
   {
      float    fx;
      float    fy;
      float    fz;
      SMvColor sDiffuse;
   };

   const unsigned long g_kulFVF_XYZDiff = (keMvFVF_XYZ|keMvFVFDiffuse);

   const SMvVertexElement g_kasDeclaration_XYZDiff[] = 
   {
      {0, 0,  keMvDeclTypeFloat3,   keMvDeclMethodDefault, keMvDeclUsagePosition, 0},
      {0, 12, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,   0},
      keMvDeclEnd() 
   };

   //
   // Position, diffuse and 1 texture
   //
   struct SMvVertex_XYZDiffTex1
   {
      float    fx;
      float    fy;
      float    fz;
      SMvColor sDiffuse;
      float    ftu0;
      float    ftv0;
   };

   const unsigned long g_kulFVF_XYZDiffTex1 = (keMvFVF_XYZ|keMvFVFDiffuse|keMvFVFTex1);

   const SMvVertexElement g_kasDeclaration_XYZDiffTex1[] = 
   {
      {0, 0,  keMvDeclTypeFloat3,   keMvDeclMethodDefault, keMvDeclUsagePosition, 0},
      {0, 12, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    0},
      {0, 16, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 0},
      keMvDeclEnd() 
   };

   //
   // Position, diffuse and 2 texture
   //
   struct SMvVertex_XYZDiffTex2
   {
      float    fx;
      float    fy;
      float    fz;
      SMvColor sDiffuse;
      float    ftu0;
      float    ftv0;
      float    ftu1;
      float    ftv1;
   };

   const unsigned long g_kulFVF_XYZDiffTex2 = (keMvFVF_XYZ|keMvFVFDiffuse|keMvFVFTex2);

   const SMvVertexElement g_kasDeclaration_XYZDiffTex2[] = 
   {
      {0, 0,  keMvDeclTypeFloat3,   keMvDeclMethodDefault, keMvDeclUsagePosition, 0},
      {0, 12, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    0},
      {0, 16, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 0},
      {0, 24, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 1},
      keMvDeclEnd() 
   };

   //
   // Position, diffuse and 4 texture
   //
   struct SMvVertex_XYZDiffTex4
   {
      float    fx;
      float    fy;
      float    fz;
      SMvColor sDiffuse;
      float    ftu0;
      float    ftv0;
      float    ftu1;
      float    ftv1;
      float    ftu2;
      float    ftv2;
      float    ftu3;
      float    ftv3;
   };

   const unsigned long g_kulFVF_XYZDiffTex4 = (keMvFVF_XYZ|keMvFVFDiffuse|keMvFVFTex4);

   const SMvVertexElement g_kasDeclaration_XYZDiffTex4[] = 
   {
      {0, 0,  keMvDeclTypeFloat3,   keMvDeclMethodDefault, keMvDeclUsagePosition, 0},
      {0, 12, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    0},
      {0, 16, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 0},
      {0, 24, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 1},
      {0, 32, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 2},
      {0, 40, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 3},
      keMvDeclEnd() 
   };

   //
   // Position and 1 texture
   //
   struct SMvVertex_XYZTex1
   {
      float    fx;
      float    fy;
      float    fz;
      float    ftu0;
      float    ftv0;
   };

   const unsigned long g_kulFVF_XYZTex1 = (keMvFVF_XYZ|keMvFVFTex1);

   const SMvVertexElement g_kasDeclaration_XYZTex1[] = 
   {
      {0, 0,  keMvDeclTypeFloat3,   keMvDeclMethodDefault, keMvDeclUsagePosition, 0},
      {0, 12, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 0},
      keMvDeclEnd() 
   };

   //
   // Position and 2 texture
   //
   struct SMvVertex_XYZTex2
   {
      float    fx;
      float    fy;
      float    fz;
      float    ftu0;
      float    ftv0;
      float    ftu1;
      float    ftv1;
   };

   const unsigned long g_kulFVF_XYZTex2 = (keMvFVF_XYZ|keMvFVFTex2);

   const SMvVertexElement g_kasDeclaration_XYZTex2[] = 
   {
      {0, 0,  keMvDeclTypeFloat3,   keMvDeclMethodDefault, keMvDeclUsagePosition, 0},
      {0, 12, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 0},
      {0, 20, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 1},
      keMvDeclEnd() 
   };

   //
   // Position and 4 texture
   //
   struct SMvVertex_XYZTex4
   {
      float    fx;
      float    fy;
      float    fz;
      float    ftu0;
      float    ftv0;
      float    ftu1;
      float    ftv1;
      float    ftu2;
      float    ftv2;
      float    ftu3;
      float    ftv3;
   };

   const unsigned long g_kulFVF_XYZTex4 = (keMvFVF_XYZ|keMvFVFTex4);

   const SMvVertexElement g_kasDeclaration_XYZTex4[] = 
   {
      {0, 0,  keMvDeclTypeFloat3,   keMvDeclMethodDefault, keMvDeclUsagePosition, 0},
      {0, 12, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 0},
      {0, 20, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 1},
      {0, 28, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 2},
      {0, 36, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 3},
      keMvDeclEnd() 
   };

   //
   // Position, diffuse and specular
   //
   struct SMvVertex_XYZDiffSpec
   {
      float    fx;
      float    fy;
      float    fz;
      SMvColor sDiffuse;
      SMvColor sSpecular;
   };

   const unsigned long g_kulFVF_XYZDiffSpec = (keMvFVF_XYZ|keMvFVFDiffuse|keMvFVFSpecular);
   
   const SMvVertexElement g_kasDeclaration_XYZDiffSpec[] = 
   {
      {0, 0,  keMvDeclTypeFloat3,   keMvDeclMethodDefault, keMvDeclUsagePosition, 0},
      {0, 12, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    0},
      {0, 16, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    1},
      keMvDeclEnd() 
   };

   //
   // Position, diffuse, specular and 1 texture
   //
   struct SMvVertex_XYZDiffSpecTex1
   {
      float    fx;
      float    fy;
      float    fz;
      SMvColor sDiffuse;
      SMvColor sSpecular;
      float    ftu0;
      float    ftv0;
   };

   const unsigned long g_kulFVF_XYZDiffSpecTex1 = (keMvFVF_XYZ|keMvFVFDiffuse|keMvFVFSpecular|keMvFVFTex1);

   const SMvVertexElement g_kasDeclaration_XYZDiffSpecTex1[] = 
   {
      {0, 0,  keMvDeclTypeFloat3,   keMvDeclMethodDefault, keMvDeclUsagePosition, 0},
      {0, 12, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    0},
      {0, 16, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    1},
      {0, 20, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 0},
      keMvDeclEnd() 
   };

   //
   // Position, diffuse, specular and 2 texture
   //
   struct SMvVertex_XYZDiffSpecTex2
   {
      float    fx;
      float    fy;
      float    fz;
      SMvColor sDiffuse;
      SMvColor sSpecular;
      float    ftu0;
      float    ftv0;
      float    ftu1;
      float    ftv1;
   };

   const unsigned long g_kulFVF_XYZDiffSpecTex2 = (keMvFVF_XYZ|keMvFVFDiffuse|keMvFVFSpecular|keMvFVFTex2);

   const SMvVertexElement g_kasDeclaration_XYZDiffSpecTex2[] = 
   {
      {0, 0,  keMvDeclTypeFloat3,   keMvDeclMethodDefault, keMvDeclUsagePosition, 0},
      {0, 12, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    0},
      {0, 16, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    1},
      {0, 20, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 0},
      {0, 28, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 1},
      keMvDeclEnd() 
   };

   //
   // Position, diffuse, specular and 4 texture
   //
   struct SMvVertex_XYZDiffSpecTex4
   {
      float    fx;
      float    fy;
      float    fz;
      SMvColor sDiffuse;
      SMvColor sSpecular;
      float    ftu0;
      float    ftv0;
      float    ftu1;
      float    ftv1;
      float    ftu2;
      float    ftv2;
      float    ftu3;
      float    ftv3;
   };

   const unsigned long g_kulFVF_XYZDiffSpecTex4 = (keMvFVF_XYZ|keMvFVFDiffuse|keMvFVFSpecular|keMvFVFTex4);

   const SMvVertexElement g_kasDeclaration_XYZDiffSpecTex4[] = 
   {
      {0, 0,  keMvDeclTypeFloat3,   keMvDeclMethodDefault, keMvDeclUsagePosition, 0},
      {0, 12, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    0},
      {0, 16, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    1},
      {0, 20, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 0},
      {0, 28, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 1},
      {0, 36, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 2},
      {0, 44, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 3},
      keMvDeclEnd() 
   };

   //
   // Pretransformed position, diffuse
   //
   struct SMvVertex_XYZWDiff
   {
      float    fx;
      float    fy;
      float    fz;
      float    fw; 
      SMvColor sDiffuse;
   };

   const unsigned long g_kulFVF_XYZWDiff = (keMvFVF_XYZRHW|keMvFVFDiffuse);

   const SMvVertexElement g_kasDeclaration_XYZWDiff[] = 
   {
      {0, 0,  keMvDeclTypeFloat4,   keMvDeclMethodDefault, keMvDeclUsagePositionT,0},
      {0, 16, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    0},
      keMvDeclEnd() 
   };

   //
   // Pretransformed position, diffuse and 1 texture
   //
   struct SMvVertex_XYZWDiffTex1
   {
      float    fx;
      float    fy;
      float    fz;
      float    fw; 
      SMvColor sDiffuse;
      float    ftu0;
      float    ftv0;
   };

   const unsigned long g_kulFVF_XYZWDiffTex1 = (keMvFVF_XYZRHW|keMvFVFDiffuse|keMvFVFTex1);

   const SMvVertexElement g_kasDeclaration_XYZWDiffTex1[] = 
   {
      {0, 0,  keMvDeclTypeFloat4,   keMvDeclMethodDefault, keMvDeclUsagePositionT,0},
      {0, 16, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    0},
      {0, 20, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 0},
      keMvDeclEnd() 
   };


   //
   // Pretransformed position, diffuse and 2 texture
   //
   struct SMvVertex_XYZWDiffTex2
   {
      float    fx;
      float    fy;
      float    fz;
      float    fw; 
      SMvColor sDiffuse;
      float    ftu0;
      float    ftv0;
      float    ftu1;
      float    ftv1;
   };

   const unsigned long g_kulFVF_XYZWDiffTex2 = (keMvFVF_XYZRHW|keMvFVFDiffuse|keMvFVFTex2);

   const SMvVertexElement g_kasDeclaration_XYZWDiffTex2[] = 
   {
      {0, 0,  keMvDeclTypeFloat4,   keMvDeclMethodDefault, keMvDeclUsagePositionT,0},
      {0, 16, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    0},
      {0, 20, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 0},
      {0, 28, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 1},
      keMvDeclEnd() 
   };

   //
   // Pretransformed position, diffuse and 4 texture
   //
   struct SMvVertex_XYZWDiffTex4
   {
      float    fx;
      float    fy;
      float    fz;
      float    fw; 
      SMvColor sDiffuse;
      float    ftu0;
      float    ftv0;
      float    ftu1;
      float    ftv1;
      float    ftu2;
      float    ftv2;
      float    ftu3;
      float    ftv3;
   };

   const unsigned long g_kulFVF_XYZWDiffTex4 = (keMvFVF_XYZRHW|keMvFVFDiffuse|keMvFVFTex4);

   const SMvVertexElement g_kasDeclaration_XYZWDiffTex4[] = 
   {
      {0, 0,  keMvDeclTypeFloat4,   keMvDeclMethodDefault, keMvDeclUsagePositionT,0},
      {0, 16, keMvDeclTypeD3DColor, keMvDeclMethodDefault, keMvDeclUsageColor,    0},
      {0, 20, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 0},
      {0, 28, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 1},
      {0, 36, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 2},
      {0, 44, keMvDeclTypeFloat2,   keMvDeclMethodDefault, keMvDeclUsageTexCoord, 3},
      keMvDeclEnd() 
   };

   //
   // Vertices for per-pixel lighting with precomputed normal, tangent and binormal
   //
   struct SMvVertex_PerPixelLighting
   {
      // position
      float fx;
      float fy;
      float fz;
      // normal
      float fnx;
      float fny;
      float fnz;
      // tangent
      float ftx;
      float fty;
      float ftz;
      // binormal
      float fbx;
      float fby;
      float fbz;
      // texture coordinates
      float ftu0;
      float ftv0;
   };

   const SMvVertexElement g_kasDeclaration_PerPixelLighting[] = 
   {
      {0, 0,  keMvDeclTypeFloat3, keMvDeclMethodDefault, keMvDeclUsagePosition, 0},
      {0, 12, keMvDeclTypeFloat3, keMvDeclMethodDefault, keMvDeclUsageNormal,   0},
      {0, 24, keMvDeclTypeFloat3, keMvDeclMethodDefault, keMvDeclUsageTangent,  0},
      {0, 36, keMvDeclTypeFloat3, keMvDeclMethodDefault, keMvDeclUsageBinormal, 0},
      {0, 48, keMvDeclTypeFloat2, keMvDeclMethodDefault, keMvDeclUsageTexCoord, 0},
      keMvDeclEnd() 
   };

}

#endif