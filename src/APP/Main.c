unsigned char SW1_input(void){
return GPIO_PORTF_DATA_R & 0x10;
}
unsigned char SW2_input(void){
return GPIO_PORTF_DATA_R & 0x01;
}
void LEDs_output(unsigned char data){
GPIO_PORTF_DATA_R &= ~0x0E; //clearing bits
GPIO_PORTF_DATA_R |= data;
}



unsigned char push_button;

int main() {
	while(1){
		
		push_button = "SW1_input()";	//Between " " add function name of SW1 that returns current state of switch
		
		while((push_button == 0x10) & (distance < 100 )){
			//Put trajectories
		}
		LEDs_output(RED);
	}
}
