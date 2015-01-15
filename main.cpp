/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
extern "C" {
    #include "fxlib.h"
    #include "fx-monochromelib/include/MonochromeLib.h"
    #include "time.h"
}

#include "Matrices.h"
#include "FxGL.h"

int main() {
    float z = 0, r = 0;

    ML_clear_vram();
        
    // Face devant
    GL_VertexPush(Vector3(-1, -1, -1));
    GL_VertexPush(Vector3( 1, -1, -1));
    GL_VertexPush(Vector3(-1, -1, -1));
    GL_VertexPush(Vector3(-1,  1, -1));
    GL_VertexPush(Vector3( 1, -1, -1));
    GL_VertexPush(Vector3( 1,  1, -1));
    GL_VertexPush(Vector3( 1,  1, -1));
    GL_VertexPush(Vector3(-1,  1, -1));

    // Face derrière
    GL_VertexPush(Vector3(-1, -1,  1));
    GL_VertexPush(Vector3( 1, -1,  1));
    GL_VertexPush(Vector3(-1, -1,  1));
    GL_VertexPush(Vector3(-1,  1,  1));
    GL_VertexPush(Vector3( 1, -1,  1));
    GL_VertexPush(Vector3( 1,  1,  1));
    GL_VertexPush(Vector3( 1,  1,  1));
    GL_VertexPush(Vector3(-1,  1,  1));

    // Et on relie
    GL_VertexPush(Vector3(-1,  1, -1));
    GL_VertexPush(Vector3(-1,  1,  1));
    GL_VertexPush(Vector3( 1,  1, -1));
    GL_VertexPush(Vector3( 1,  1,  1));

    GL_VertexPush(Vector3(-1, -1, -1));
    GL_VertexPush(Vector3(-1, -1,  1));
    GL_VertexPush(Vector3( 1, -1, -1));
    GL_VertexPush(Vector3( 1, -1,  1));

    // Et le repère
    GL_VertexPush(Vector3( 0,  0,  0));
    GL_VertexPush(Vector3( 1,  0,  0));
    GL_VertexPush(Vector3( 0,  0,  0));
    GL_VertexPush(Vector3( 0,  1,  0));
    GL_VertexPush(Vector3( 0,  0,  0));
    GL_VertexPush(Vector3( 0,  0,  1));

    GL_SetProjectionMatrix(
        GL_ProjectionMatrixFovRH(25 * DEG2RAD, 1, 0.1, 2000)
    );

    while(1) {
        GL_SetViewMatrix(
            GL_LookAtMatrixRH(
                Vector3(r, z, 3),
                Vector3(0, 0, 0),
                Vector3(0, 1, 0)
            )
        );

        GL_Clear();
        GL_Draw();
        
        if(IsKeyDown(KEY_CTRL_UP))
            z += 0.1;
        if(IsKeyDown(KEY_CTRL_DOWN))
            z -= 0.1;
        if(IsKeyDown(KEY_CTRL_LEFT))
            r += 0.1;
        if(IsKeyDown(KEY_CTRL_RIGHT))
            r -= 0.1;
            
        if(IsKeyDown(KEY_CTRL_EXE))
            z = r = 0;
    }

    GL_VertexFree();

    return 1;    
}

extern "C" {

//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int AddIn_main(int isAppli, unsigned short OptionNum)
{
    return main();
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


    #pragma section _BR_Size
    unsigned long BR_Size;
    #pragma section


    #pragma section _TOP

    //****************************************************************************
    //  InitializeSystem
    //
    //  param   :   isAppli   : 1 = Application / 0 = eActivity
    //              OptionNum : Option Number (only eActivity)
    //
    //  retval  :   1 = No error / 0 = Error
    //
    //****************************************************************************
    int InitializeSystem(int isAppli, unsigned short OptionNum)
    {
        return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
    }

    #pragma section

}