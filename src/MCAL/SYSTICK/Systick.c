void Systick_Init(void){
    NVIC_ST_CTRL_R=0;
    NVIC_ST_RELOAD_R=0x00FFFFFF;
    NVIC_ST_CURRENT_R=0;
    NVIC_ST_CTRL_R=0x00000007;  
}
void Systick_Wait(unit32_t delay){
    NVIC_ST_RELOAD_R=delay-1;
    NVIC_ST_CURRENT_R=0;
    while(NVIC_ST_CTRL_R&0x00010000==0);  
}
