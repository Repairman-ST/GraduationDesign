/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "includes.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0 (GUI_ID_USER + 0x01)
#define ID_SCROLLBAR_0 (GUI_ID_USER + 0x02)
#define ID_SLIDER_0 (GUI_ID_USER + 0x03)
#define ID_TEXT_0 (GUI_ID_USER + 0x04)


/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static  float  temp;
static  char   textBuff[20];

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 320, 240, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 117, 68, 80, 20, 0, 0x0, 0 },
  { SCROLLBAR_CreateIndirect, "Scrollbar", ID_SCROLLBAR_0, 75, 160, 160, 20, 0, 0x0, 0 },
  { SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 77, 110, 157, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "0.0", ID_TEXT_0, 2, 10, 128, 20, 0, 0x0, 0 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       _cbDialog 回调函数
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
    WM_HWIN hItem;
    int     NCode;
    int     Id;

    switch (pMsg->MsgId) {

        case WM_INIT_DIALOG:                                        // Initialization of 'Framewin'
            hItem = pMsg->hWin;
            FRAMEWIN_SetFont(hItem, GUI_FONT_32B_ASCII);
            FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetTextColor(hItem, GUI_MAKE_COLOR(0x000000FF));
            FRAMEWIN_SetText(hItem, "2018");

            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);        // Initialization of 'Text'
            TEXT_SetFont(hItem, GUI_FONT_16B_ASCII);
            TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);      // Initialization of 'Button'
            BUTTON_SetText(hItem, "LED1");
            break;

        case WM_PAINT:
			GUI_SetBkColor(0x00C290FF);
            GUI_Clear();
            break;

        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hItem, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hItem, 0);
                    break;
            }
            break;

        case WM_TIMER:                                               // 定时器消息
			temp = BSP_18B20_TempTran(BSP_18B20_GetTempFast());      
			sprintf(textBuff, "Temp: %.2f `C", temp);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
            TEXT_SetText(hItem, (const char *)textBuff);
            WM_RestartTimer(pMsg->Data.v, 500);                     // 初始化定时器初值1s
            break;

        case WM_NOTIFY_PARENT:
            Id    = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
            switch(Id) {

                case ID_BUTTON_0: // Notifications sent by 'Button'
                    switch(NCode) {

                        case WM_NOTIFICATION_CLICKED:       // 通知按键被点击
							BSP_LED_Toggle(1);
                            break;

                        case WM_NOTIFICATION_RELEASED:      // 通知按键被释放
                            break;
                    }
                    break;

            case ID_SCROLLBAR_0: // Notifications sent by 'Scrollbar'
                switch(NCode) {
                    case WM_NOTIFICATION_CLICKED:
                        break;

                    case WM_NOTIFICATION_RELEASED:
                        break;

                    case WM_NOTIFICATION_VALUE_CHANGED:
                        break;
                }
                break;

            case ID_SLIDER_0: // Notifications sent by 'Slider'
                switch(NCode) {
                    case WM_NOTIFICATION_CLICKED:
                        break;

                    case WM_NOTIFICATION_RELEASED:
                        break;

                    case WM_NOTIFICATION_VALUE_CHANGED:
                        break;
                }
                break;
            }
        break;

        default:
            WM_DefaultProc(pMsg);
            break;
    }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFramewin
*/
WM_HWIN CreateFramewin(void);
WM_HWIN CreateFramewin(void) {
    WM_HWIN hWin;

    hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
    return hWin;
}


void MainTask(void)
{
    WM_HWIN   hDlg;               // 窗口句柄
    WM_HTIMER hTimer;             // 定时器变量

    // 窗口使能使用内存设备，防止闪烁，放在GUI_Init()之前可以保证所有
    // 窗口都能使用动态内存设备
    WM_SetCreateFlags(WM_CF_MEMDEV);

    GUI_Init();

    // 创建一个窗口并且返回一个句柄
    hDlg = CreateFramewin();

    // 创建一个定时器
    hTimer = WM_CreateTimer(WM_GetClientWindow(hDlg), 0, 100, 0);


    while (1) {
        GUI_Delay(10);
    }

}


// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
