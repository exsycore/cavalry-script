#if defined _inc_header
    #undef _inc_header
#endif

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

#define ATM_TABLE       "atms"
#define MAX_ATM         (100)
#define MODEL_ATM       (19324)
#define ATM_USE_RANGE   (2.5)
#define ATM_LABEL_COLOR (0x00DD00FF)
#define ATM_TEXT "[ATM]\n{FFFFFF}กด 'N' เพื่อใช้งาน"

#define ATM_PAGE_NONE       0
#define ATM_PAGE_MAIN       1
#define ATM_PAGE_NUMPAD     2
#define ATM_PAGE_TRANSFER   3

#define ATM_MODE_WITHDRAW   0
#define ATM_MODE_DEPOSIT    1
#define ATM_MODE_TRANSFER   2

// สถานะของผู้เล่นในหน้า ATM
new ATM_Page[MAX_PLAYERS]       = {ATM_PAGE_NONE, ...};
new ATM_Mode[MAX_PLAYERS]       = {ATM_MODE_WITHDRAW, ...};
new ATM_InputAmount[MAX_PLAYERS]= {0, ...};             // จำนวนที่กด numpad
new ATM_TransferTarget[MAX_PLAYERS] = {INVALID_PLAYER_ID, ...};

new PlayerText:atm_main[MAX_PLAYERS][21];
new PlayerText:atm_cash_text[MAX_PLAYERS];
new PlayerText:atm_balance_text[MAX_PLAYERS];
new PlayerText:atm_withdraw_btn[MAX_PLAYERS]; // ปุ่มถอนกดแล้ว atm_page_input_x จะต้องแสดงขึ้นมา
new PlayerText:atm_deposit_btn[MAX_PLAYERS]; // ปุ่มฝากกดแล้ว atm_page_input_x จะต้องแสดงขึ้นมา
new PlayerText:atm_quick_withdraw_btn_0[MAX_PLAYERS]; // ปุ่มถอนเงินรวดเร็ว 100
new PlayerText:atm_quick_withdraw_btn_1[MAX_PLAYERS]; // ปุ่มถอนเงินรวดเร็ว 500
new PlayerText:atm_quick_withdraw_btn_2[MAX_PLAYERS]; // ปุ่มถอนเงินรวดเร็ว 1000
new PlayerText:atm_quick_deposit_all_btn[MAX_PLAYERS]; // ปุ่มฝากเงินทั้งหมดทีเรามี
new PlayerText:atm_exit_btn[MAX_PLAYERS];
new PlayerText:atm_num_7_btn[MAX_PLAYERS];
new PlayerText:atm_num_8_btn[MAX_PLAYERS];
new PlayerText:atm_num_9_btn[MAX_PLAYERS];
new PlayerText:atm_num_4_btn[MAX_PLAYERS];
new PlayerText:atm_num_5_btn[MAX_PLAYERS];
new PlayerText:atm_num_6_btn[MAX_PLAYERS];
new PlayerText:atm_num_1_btn[MAX_PLAYERS];
new PlayerText:atm_num_2_btn[MAX_PLAYERS];
new PlayerText:atm_num_3_btn[MAX_PLAYERS];
new PlayerText:atm_num_0_btn[MAX_PLAYERS];
new PlayerText:atm_num_clear_btn[MAX_PLAYERS];
new PlayerText:atm_num_0[MAX_PLAYERS];
new PlayerText:atm_num_1[MAX_PLAYERS];
new PlayerText:atm_num_2[MAX_PLAYERS];
new PlayerText:atm_num_3[MAX_PLAYERS];
new PlayerText:atm_num_4[MAX_PLAYERS];
new PlayerText:atm_num_5[MAX_PLAYERS];
new PlayerText:atm_num_6[MAX_PLAYERS];
new PlayerText:atm_num_7[MAX_PLAYERS];
new PlayerText:atm_num_8[MAX_PLAYERS];
new PlayerText:atm_num_10[MAX_PLAYERS];
new PlayerText:atm_num_9[MAX_PLAYERS];
new PlayerText:atm_page_input_0[MAX_PLAYERS];
new PlayerText:atm_page_input_1[MAX_PLAYERS];
new PlayerText:atm_page_input_2[MAX_PLAYERS];
new PlayerText:atm_page_input_3[MAX_PLAYERS];
new PlayerText:atm_page_input_4[MAX_PLAYERS];
new PlayerText:atm_page_input_5[MAX_PLAYERS];
new PlayerText:atm_page_input_6[MAX_PLAYERS]; // atm_page_input_6 is cash text
new PlayerText:atm_page_input_7[MAX_PLAYERS]; // atm_page_input_7 is balance text
new PlayerText:atm_page_input_8[MAX_PLAYERS];
new PlayerText:atm_page_input_9[MAX_PLAYERS]; // atm_page_input_9 คือ text withdraw เอาไว้เปลี่ยนเวลาผู้เล่นกด deposit ก็เปลี่ยน text นี้ไปด้วย
new PlayerText:atm_page_input_10[MAX_PLAYERS]; // atm_page_input_10 คือ จำนวนเงินที่ต้องการโอนหรือถอน
new PlayerText:atm_confirm_btn[MAX_PLAYERS]; // atm_confirm_btn ปุ่มตกลงเอาไว้ขึ้นตอนที่ผู้เล่นกด withdraw หรือ deposit แล้วเท่านั้น

enum E_ATM {
    E_ATM_id,
    E_ATM_interior,
    E_ATM_world,

    Float:E_ATM_x,
    Float:E_ATM_y,
    Float:E_ATM_z,
    Float:E_ATM_rx,
    Float:E_ATM_ry,
    Float:E_ATM_rz,

    STREAMER_TAG_OBJECT:E_ATM_obj,
    Text3D:E_ATM_label,

    bool:E_ATM_exists
}

new ATMData[MAX_ATM][E_ATM];

new ATM_EditingID[MAX_PLAYERS] = {-1, ...};

forward ATMLoad();
forward OnATMCreated(atmid);