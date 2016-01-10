#ifndef TFT_DRIVER_H
#define TFT_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

extern const unsigned short Black;
extern const unsigned short Red;
extern const unsigned short Green;
extern const unsigned short Blue;
extern const unsigned short White;
extern const unsigned short Purple;
extern const unsigned short Yellow;
extern const unsigned short Cyan;
extern const unsigned short d_gray;
extern const unsigned short l_gray;

void Write_Command(unsigned short Wcommand);

void Write_Data(unsigned short Wdata);

void Write_Command_Data(unsigned short Wcommand,unsigned short Wdata);

void TFT_Set_Address(unsigned short PX1,unsigned short PY1,unsigned short PX2,unsigned short PY2);

void TFT_Init(void);

unsigned short Set_color(unsigned short R,unsigned short G,unsigned short B);

void TFT_Fill(unsigned short color);

void TFT_Box(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2,unsigned short color);

void TFT_Dot(unsigned short x,unsigned short y,unsigned short color);

void TFT_Line(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2,unsigned short color);

void TFT_H_Line(char x1,char x2,unsigned short y_pos,unsigned short color);

void TFT_V_Line(unsigned short y1,unsigned short y2,char x_pos,unsigned short color);

void TFT_Rectangle(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2,unsigned short color);

void TFT_Circle(unsigned short x,unsigned short y,char radius,char fill,unsigned short color);

void TFT_Char(char C,unsigned short x,unsigned short y,char DimFont,unsigned short Fcolor,unsigned short Bcolor);

void TFT_Text(const char * S,unsigned short x,unsigned short y,char DimFont,unsigned short Fcolor,unsigned short Bcolor);

void TFT_Image(unsigned short pos_x,unsigned short pos_y,unsigned short dim_x,unsigned short dim_y,const unsigned short *picture);

#ifdef __cplusplus
}
#endif

#endif
