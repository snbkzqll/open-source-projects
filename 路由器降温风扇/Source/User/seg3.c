#include "seg3.h"

// 共阴字形段码表 (数字 0-9)
// Bit 0:A, Bit 1:B, Bit 2:C, Bit 3:D, Bit 4:E, Bit 5:F, Bit 6:G, Bit 7:DP
static const uint8_t seg_code[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

// 显示数据段码缓冲区，默认全灭
static volatile uint8_t disp_buf[3] = {0x00, 0x00, 0x00};

// GPIO 初始化辅助函数
static void SEG3_GPIO_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

// 数码管 GPIO 及状态初始化
void SEG3_Init(void)
{
    // 开启全部使用的 GPIO 端口时钟
    RCC_AHBPeriphClockCmd(DIG1_GPIO_CLK | DIG2_GPIO_CLK | DIG3_GPIO_CLK |
                          SEGA_GPIO_CLK | SEGB_GPIO_CLK | SEGC_GPIO_CLK | 
                          SEGD_GPIO_CLK | SEGE_GPIO_CLK | SEGF_GPIO_CLK | 
                          SEGG_GPIO_CLK | SEGDP_GPIO_CLK, ENABLE);
    
    // 初始化 3 个位选（COM极）
    SEG3_GPIO_Init(DIG1_GPIO_PORT, DIG1_GPIO_PIN);
    SEG3_GPIO_Init(DIG2_GPIO_PORT, DIG2_GPIO_PIN);
    SEG3_GPIO_Init(DIG3_GPIO_PORT, DIG3_GPIO_PIN);
    
    // 初始化 8 个段选（阳极段）
    SEG3_GPIO_Init(SEGA_GPIO_PORT, SEGA_GPIO_PIN);
    SEG3_GPIO_Init(SEGB_GPIO_PORT, SEGB_GPIO_PIN);
    SEG3_GPIO_Init(SEGC_GPIO_PORT, SEGC_GPIO_PIN);
    SEG3_GPIO_Init(SEGD_GPIO_PORT, SEGD_GPIO_PIN);
    SEG3_GPIO_Init(SEGE_GPIO_PORT, SEGE_GPIO_PIN);
    SEG3_GPIO_Init(SEGF_GPIO_PORT, SEGF_GPIO_PIN);
    SEG3_GPIO_Init(SEGG_GPIO_PORT, SEGG_GPIO_PIN);
    SEG3_GPIO_Init(SEGDP_GPIO_PORT, SEGDP_GPIO_PIN);
    
    // 清空数码管显示
    SEG3_Clear();
}

// 写入单字节段选数据
static void SEG3_WriteSeg(uint8_t code)
{
    // A 段
    if (code & 0x01) GPIO_SetBits(SEGA_GPIO_PORT, SEGA_GPIO_PIN);
    else GPIO_ResetBits(SEGA_GPIO_PORT, SEGA_GPIO_PIN);
    
    // B 段
    if (code & 0x02) GPIO_SetBits(SEGB_GPIO_PORT, SEGB_GPIO_PIN);
    else GPIO_ResetBits(SEGB_GPIO_PORT, SEGB_GPIO_PIN);
    
    // C 段
    if (code & 0x04) GPIO_SetBits(SEGC_GPIO_PORT, SEGC_GPIO_PIN);
    else GPIO_ResetBits(SEGC_GPIO_PORT, SEGC_GPIO_PIN);
    
    // D 段
    if (code & 0x08) GPIO_SetBits(SEGD_GPIO_PORT, SEGD_GPIO_PIN);
    else GPIO_ResetBits(SEGD_GPIO_PORT, SEGD_GPIO_PIN);
    
    // E 段
    if (code & 0x10) GPIO_SetBits(SEGE_GPIO_PORT, SEGE_GPIO_PIN);
    else GPIO_ResetBits(SEGE_GPIO_PORT, SEGE_GPIO_PIN);
    
    // F 段
    if (code & 0x20) GPIO_SetBits(SEGF_GPIO_PORT, SEGF_GPIO_PIN);
    else GPIO_ResetBits(SEGF_GPIO_PORT, SEGF_GPIO_PIN);
    
    // G 段
    if (code & 0x40) GPIO_SetBits(SEGG_GPIO_PORT, SEGG_GPIO_PIN);
    else GPIO_ResetBits(SEGG_GPIO_PORT, SEGG_GPIO_PIN);
    
    // DP 小数点段
    if (code & 0x80) GPIO_SetBits(SEGDP_GPIO_PORT, SEGDP_GPIO_PIN);
    else GPIO_ResetBits(SEGDP_GPIO_PORT, SEGDP_GPIO_PIN);
}

// 动态扫描逻辑 (在定时器 1ms 中断中被调用)
void SEG3_Scan(void)
{
    static uint8_t digit_index = 0;
    
    // 1. 消隐：拉高所有位选（共阴极，高电平关闭显示，消除拖影）
    GPIO_SetBits(DIG1_GPIO_PORT, DIG1_GPIO_PIN);
    GPIO_SetBits(DIG2_GPIO_PORT, DIG2_GPIO_PIN);
    GPIO_SetBits(DIG3_GPIO_PORT, DIG3_GPIO_PIN);
    
    // 2. 更新段码引脚输出
    SEG3_WriteSeg(disp_buf[digit_index]);
    
    // 3. 打开当前显示的数字位选（低电平选通）
    if (digit_index == 0)
    {
        GPIO_ResetBits(DIG1_GPIO_PORT, DIG1_GPIO_PIN);
    }
    else if (digit_index == 1)
    {
        GPIO_ResetBits(DIG2_GPIO_PORT, DIG2_GPIO_PIN);
    }
    else if (digit_index == 2)
    {
        GPIO_ResetBits(DIG3_GPIO_PORT, DIG3_GPIO_PIN);
    }
    
    // 4. 位循环移位
    digit_index++;
    if (digit_index >= 3)
    {
        digit_index = 0;
    }
}

// 将温度解析并装载到显示缓冲区中 (零上第一位不显示且消隐高位0，零下第一位显示'-')
void SEG3_DisplayTemp(float temp)
{
    // 对温度值取绝对值并四舍五入取整
    int val = (int)(temp >= 0.0f ? (temp + 0.5f) : (-temp + 0.5f));
    
    // 限制最大显示为 99 (避免两位整数溢出)
    if (val > 99)
    {
        val = 99;
    }

    if (temp >= 0.0f)
    {
        // 零上温度：第一位不显示
        disp_buf[0] = 0x00; // 第一位空白
        
        if (val >= 10)
        {
            disp_buf[1] = seg_code[val / 10]; // 十位
            disp_buf[2] = seg_code[val % 10]; // 个位
        }
        else
        {
            disp_buf[1] = 0x00; // 十位不显示 (高位零消隐)
            disp_buf[2] = seg_code[val];      // 个位
        }
    }
    else
    {
        // 零下温度：第一位固定显示 '-'
        disp_buf[0] = 0x40; // 第一位显示负号
        
        if (val >= 10)
        {
            disp_buf[1] = seg_code[val / 10]; // 十位
            disp_buf[2] = seg_code[val % 10]; // 个位
        }
        else
        {
            disp_buf[1] = 0x00; // 十位不显示 (保持显示为 - 5)
            disp_buf[2] = seg_code[val];      // 个位
        }
    }
}

// 熄灭数码管并清零缓冲区 (低功耗休眠前调用)
void SEG3_Clear(void)
{
    // 拉高共阴极公共端以阻断电流，实现全灭
    GPIO_SetBits(DIG1_GPIO_PORT, DIG1_GPIO_PIN);
    GPIO_SetBits(DIG2_GPIO_PORT, DIG2_GPIO_PIN);
    GPIO_SetBits(DIG3_GPIO_PORT, DIG3_GPIO_PIN);
    
    // 同时拉低所有阳极段选
    GPIO_ResetBits(SEGA_GPIO_PORT, SEGA_GPIO_PIN);
    GPIO_ResetBits(SEGB_GPIO_PORT, SEGB_GPIO_PIN);
    GPIO_ResetBits(SEGC_GPIO_PORT, SEGC_GPIO_PIN);
    GPIO_ResetBits(SEGD_GPIO_PORT, SEGD_GPIO_PIN);
    GPIO_ResetBits(SEGE_GPIO_PORT, SEGE_GPIO_PIN);
    GPIO_ResetBits(SEGF_GPIO_PORT, SEGF_GPIO_PIN);
    GPIO_ResetBits(SEGG_GPIO_PORT, SEGG_GPIO_PIN);
    GPIO_ResetBits(SEGDP_GPIO_PORT, SEGDP_GPIO_PIN);
    
    // 清空缓冲区
    disp_buf[0] = 0x00;
    disp_buf[1] = 0x00;
    disp_buf[2] = 0x00;
}
