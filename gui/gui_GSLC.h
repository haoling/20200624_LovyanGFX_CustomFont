//<File !Start!>
// FILE: [gui_GSLC.h]
// Created by GUIslice Builder version: [0.14.b004]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XTextbox.h"
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if !defined(DRV_DISP_TFT_ESPI)
  #error Builder config "Edit->Options->General->Target Platform" should be "arduino"
#endif 
#include <TFT_eSPI.h>
#include <Adafruit_GFX.h>
// Note that these files are located within the Adafruit-GFX library folder:
#include "Fonts/JF-Dot-Shinonome125pt8b.h"
#include "Fonts/JF-Dot-Shinonome128pt8b.h"
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PROJECT_OPTIONS,E_PG_MAIN};
enum {E_ELEM_TEXT1,E_ELEM_TEXTBOX1};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {JF_DOT_SHINONOME125_8,JF_DOT_SHINONOME128_8,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                2

#define MAX_ELEM_PROJECT_OPTIONS 0 // # Elems total on page
#define MAX_ELEM_PROJECT_OPTIONS_RAM MAX_ELEM_PROJECT_OPTIONS // # Elems in RAM

#define MAX_ELEM_PG_MAIN 2 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asProject1Elem[MAX_ELEM_PROJECT_OPTIONS_RAM];
gslc_tsElemRef                  m_asProject1ElemRef[MAX_ELEM_PROJECT_OPTIONS];
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsXTextbox                 m_sTextbox1;
char                            m_acTextboxBuf1[684]; // NRows=18 NCols=38

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemText1;
extern gslc_tsElemRef* m_pElemTextbox1;
extern gslc_tsElemRef* m_pTextSlider1;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,JF_DOT_SHINONOME125_8,GSLC_FONTREF_PTR,&JF_Dot_Shinonome125pt8b,1)) { return; }
    if (!gslc_FontSet(&m_gui,JF_DOT_SHINONOME128_8,GSLC_FONTREF_PTR,&JF_Dot_Shinonome128pt8b,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
   
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_TEXTBOX1,E_PG_MAIN,&m_sTextbox1,
    (gslc_tsRect){0,25,240,240},JF_DOT_SHINONOME125_8,
    (char*)&m_acTextboxBuf1,18,38);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_COL_BLACK);
  m_pElemTextbox1 = pElemRef;
  
  // Create E_ELEM_TEXT1 runtime modifiable text
  static char m_sDisplayText1[41] = "ESP32";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT1,E_PG_MAIN,(gslc_tsRect){0,0,360,21},
    (char*)m_sDisplayText1,41,JF_DOT_SHINONOME128_8);
  m_pElemText1 = pElemRef;
  gslc_ElemSetTxtEnc(&m_gui,m_pElemText1,GSLC_TXT_ENC_UTF8);
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
