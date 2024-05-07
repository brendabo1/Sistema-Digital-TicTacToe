#include <intelfpgaup/KEY.h>
#include <stdio.h>

int main() {

	int KEY_data = 0;	
	int var = 0;
	if (!KEY_open()) printf("deu ruim familia");
	
	while (1) {
	if(KEY_read(&KEY_data)) {

		if(KEY_data ==1) {
		var = 1;
		printf("foi acionado %d\n", var);
		break;
}
else if(KEY_data == 2) {
	var = 2;
	printf("foi acionado  %d\n", var);
} else if (KEY_data == 4) {
	var = 3;
	printf("foi acionado %d\n", var);
} else if (KEY_data == 8) {
	var = 4;
	printf("foi acionado %d\n", var);
}
	}
}	


	return 0;
}
