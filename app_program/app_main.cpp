/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 BSP
 *
 *    Copyright (C) 2022-2023 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2023/05.
 *
 *----------------------------------------------------------------------
 */

/*
 *	app_main.c
 *	Application main program for RaspberryPi Pico
 */
#include <tk/tkernel.h>
#include <bsp/libbsp.h>
#include <sys/sysdef.h>
class PadControl
{
private:
    const UW BASE = 0x4001c000;
    const UH GPIO0 = 0x04;
public:
    enum class DriveStrength{
        DS_2MA = 0x0,
        DS_4MA = 0x1,
        DS_8MA = 0x2,
        DS_12MA = 0x3,
    };
    PadControl()
    {
        //リセット・リセット解除
        BOOL is_done_reset = *(_UW*)(0x4000C000 + 0x08) & (1<<8);
        if(is_done_reset) return;

        *(_UW*)(0x4000C000 + 0x00) |= (1<<8);
        *(_UW*)(0x4000C000 + 0x00) &= ~(1<<8);
        while (!(*(_UW*)(0x4000C000 + 0x08) & (1<<8))) {}
    };

    void SetGPIO(UB pin, 
                 BOOL slew_rate=FALSE, 
                 BOOL enable_schmitt_trigger=TRUE, 
                 BOOL enable_pull_down=TRUE, 
                 BOOL enable_pull_up=FALSE, 
                 DriveStrength drive_strength=DriveStrength::DS_4MA,
                 BOOL enable_input=TRUE, 
                 BOOL disable_output=FALSE)
    {
        UW address = BASE + GPIO0 + 0x04 * pin;
        *(_UW*)address = 0x00000000 |
                         disable_output << 7 |
                         enable_input << 6  |
                         (UB)drive_strength << 4 |
                         enable_pull_up << 3 |
                         enable_pull_down << 2 |
                         enable_schmitt_trigger << 1 |
                         slew_rate;
    };
};
class IOBank
{
private:
    const UW BASE = 0x40014000;
    const UH GPIO0_CTRL = 0x004;
public:
    enum class OutOver{
        NORMAL = 0x0,
        INVERT = 0x1,
        LOW = 0x2,
        HIGH = 0x3
    };
    enum class OeOver{
        NORMAL = 0x0,
        INVERT = 0x1,
        DISABLE = 0x2,
        ENABLE = 0x3
    };
    enum class InOver{
        NORMAL = 0x0,
        INVERT = 0x1,
        LOW = 0x2,
        HIGH = 0x3
    };
    enum class IrqOver{
        NORMAL = 0x0,
        INVERT = 0x1,
        LOW = 0x2,
        HIGH = 0x3
    };
    IOBank()
    {
        //リセット・リセット解除
        BOOL is_done_reset = *(_UW*)(0x4000C000 + 0x08) & (1<<5);
        if(is_done_reset) return;

        *(_UW*)(0x4000C000 + 0x00) |= (1<<5);
        *(_UW*)(0x4000C000 + 0x00) &= ~(1<<5);
        while (!(*(_UW*)(0x4000C000 + 0x08) & (1<<5))) {}
    };

    void SetGPIOControl(UB pin,
                        UH func_select,
                        OutOver out_over=OutOver::NORMAL,
                        OeOver oe_over=OeOver::NORMAL,
                        InOver in_over=InOver::NORMAL,
                        IrqOver irq_over=IrqOver::NORMAL)
    {
        UW address = BASE + GPIO0_CTRL + 0x8 * pin;
        *(_UW*)address = 0x00000000 |
                         func_select |
                         (UB)out_over << 8 |
                         (UB)oe_over << 12 |
                         (UB)in_over << 16 |
                         (UB)irq_over << 28;
                         
    };
};
class PIO
{
private:
    const UW BASE0 = 0x50200000;
    const UW BASE1 = 0x50300000;
    UW BASE = BASE0;
    const UH CTRL=0x000;
    const UH SM0_CLKDIV=0x0C8;
    const UH SM0_EXECCTRL=0x0CC;
    const UH SM0_SHIFTCTRL=0x0D0;
    const UH SM0_ADDR=0x0D4;
    const UH SM0_INSTR=0x0D8;
    const UH SM0_PINCTRL=0x0DC;
    const UH INSTR_MEM0=0x048;
    const UH TXF0=0x010;
public:
    PIO()
    {
        //リセット・リセット解除
        BOOL is_done_reset = *(_UW*)(0x4000C000 + 0x08) & (1<<10);
        if(is_done_reset) return;

        *(_UW*)(0x4000C000 + 0x00) |= (1<<10);
        *(_UW*)(0x4000C000 + 0x00) &= ~(1<<10);
        while (!(*(_UW*)(0x4000C000 + 0x08) & (1<<10))) {}
    };

    void SetCTRL(UB enable_sm_mask=0b0000,
                 UB sm_restart_mask=0b0000,
                 UB clock_div_restart_mask=0b0000)
    {
        *(_UW*)(BASE + CTRL) = 0x00000000 |
                             clock_div_restart_mask << 8 |
                             sm_restart_mask << 4 |
                             enable_sm_mask;                     
    };
    void SetSMClockDiv(UB sm_no=0,
                       UH div_int=0x0001,
                       UB div_frac=0x00)
    {
        UW address = BASE + SM0_CLKDIV+sm_no*24;
        *(_UW*)address = 0x00000000 |
                         div_int << 16 |
                         div_frac << 8;
    };
    void SetSMExecCtrl(UB sm_no=0,
                       UB status_n=0x0,
                       BOOL status_sel=0x0,
                       UH wrap_bottom=0x00,
                       UH wrap_top=0x1f,
                       BOOL out_sticky=FALSE,
                       BOOL inline_out_en=FALSE,
                       UH out_en_sel=0x00,
                       UH jmp_pin=0x00,
                       BOOL side_pindir=FALSE,
                       BOOL side_enable=FALSE,
                       BOOL exec_stalled=FALSE)
    {
        UW address = BASE + SM0_EXECCTRL+sm_no*24;
        *(_UW*)address = 0x00000000 |
                         exec_stalled << 31 |
                         side_enable << 30 |
                         side_pindir << 29 |
                         jmp_pin << 24 |
                         out_en_sel << 19 |
                         inline_out_en << 18 |
                         out_sticky << 17 |
                         wrap_top << 12 |
                         wrap_bottom << 7 |
                         status_sel << 4 |
                         status_n;
    };
    void SetSMExecCtrlRaw(UB sm_no=0,UW value=0x00000000)
    {
        UW address = BASE + SM0_EXECCTRL+sm_no*24;
        *(_UW*)address = value;
    };
    void SetSMShiftCtrl(UB sm_no=0,
                        BOOL auto_push=FALSE,
                        BOOL auto_pull=FALSE,
                        BOOL in_shift_dir=TRUE,
                        BOOL out_shift_dir=TRUE,
                        UH push_thresh=0x00,
                        UH pull_thresh=0x00,
                        BOOL joint_tx=FALSE,
                        BOOL joint_rx=FALSE)
    {
        UW address = BASE + SM0_SHIFTCTRL+sm_no*24;
        *(_UW*)address = 0x00000000 |
                         joint_rx << 31 |
                         joint_tx << 30 |
                         pull_thresh << 25 |
                         push_thresh << 20 |
                         out_shift_dir << 19 |
                         in_shift_dir << 18 |
                         auto_pull << 17|
                         auto_push << 16;
    };

    UW ReadSMAddr(UB sm_no=0)
    {
        UW address = BASE + SM0_ADDR+sm_no*24;
        return *(_UW*)address;
    };

    void SetSMInstr(UB sm_no=0,
                    UH instruction=0x0000)
    {
        UW address = BASE + SM0_INSTR+sm_no*24;
        *(_UW*)address = 0x00000000 |
                         instruction;
    };

    void SetSMPinCtrl(UB sm_no=0,
                      UH out_base=0x00,
                      UH set_base=0x00,
                      UH sideset_base=0x00,
                      UH in_base=0x00,
                      UH out_count=0x00,
                      UB set_count=0x5,
                      UB sideset_count=0x0)
    {
        UW address = BASE + SM0_PINCTRL+sm_no*24;
        *(_UW*)address = 0x00000000 |
                         sideset_count << 29 |
                         set_count << 26 |
                         out_count << 20 |
                         in_base << 15 |
                         sideset_base << 10 |
                         set_base << 5 |
                         out_base;
    };
    
    void SetSMPinCtrlRaw(UB sm_no=0,UW value=0x00000000)
    {
        UW address = BASE + SM0_PINCTRL+sm_no*24;
        *(_UW*)address = value;
    };
    void SetInstrMem(const UH* instructions,
                     UH instructions_num,
                     UH set_offset=0)
    {
        for (UH i = 0; i < 32; i++)
        {
            *(_UW*)(BASE + INSTR_MEM0+i*0x04) = 0x00000000;
        }
        for (UH i = 0; i < instructions_num; i++)
        {
            *(_UW*)(BASE + INSTR_MEM0+(i+set_offset)*0x04) = 0x00000000 |
                                                             instructions[i];

        }
    };

    void SetTXF(UB sm_no=0,
                UW value=0x00000000)
    {
        UW address = BASE + TXF0+sm_no*4;
        *(_UW*)address = value;
    }

    UW ReadSMPinCtrl(UB sm_no=0)
    {
        UW address = BASE + SM0_PINCTRL+sm_no*24;
        return *(_UW*)address;
    }

    UW ReadSMExecCtrl(UB sm_no=0)
    {
        UW address = BASE + SM0_EXECCTRL+sm_no*24;
        return *(_UW*)address;
    }

    UW ReadDBGPADOE()
    {
        UW address = BASE + 0x040;
        return *(_UW*)address; 
    }
};

LOCAL UH program_instructions[] = {
    0b1110000010000001,
    0b1110000000000001,
    0b0000000000000001,
};


extern "C" EXPORT INT usermain(void)
{
    PadControl pad_control;
    pad_control.SetGPIO(16,
                        FALSE,
                        TRUE,
                        FALSE,
                        FALSE,
                        PadControl::DriveStrength::DS_4MA,
                        FALSE,
                        FALSE);

    IOBank io_bank;
    io_bank.SetGPIOControl(16,6);
    
    PIO pio;
    pio.SetInstrMem(program_instructions,3,0);
    pio.SetSMPinCtrl(
        3,
        16,
        16,
        0,
        0,
        1,
        1,
        0);
    pio.SetSMExecCtrl(
        3,
        0x0,
        0x0,
        0x00,
        0x02,
        TRUE,
        FALSE,
        0x00,
        0x00,
        FALSE,
        FALSE,
        FALSE
    );
    pio.SetSMClockDiv(3,0xFFF0,0);
    pio.SetCTRL(
        0b0000,
        0b1111,
        0b1111);
    pio.SetCTRL(
        0b1111,
        0b0000,
        0b0000);
    return 0;
}
