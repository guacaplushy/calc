#include <stdio.h>
#include <windows.h>

int main() {
	char title[] = "C Calculator";
	SetConsoleTitle(title);
	printf("Hello!\n");
	printf("Operation type: ");
	char operationType[100];
	scanf("%s", operationType);
	if (strcmp(operationType, "addition") == 0) {
		printf("Enter the first number: ");
		unsigned long long first, second;
		scanf("%lld", &first);
		printf("Enter the second number: ");
		scanf("%lld", &second);
		unsigned long long result = first + second;
		printf("%lld", result);
	} else if (strcmp(operationType, "multiplication") == 0) {
		printf("Enter the first number: ");
		unsigned long long first, second;
		scanf("%lld", &first);
		printf("Enter the second number: ");
		scanf("%lld", &second);
		unsigned long long result = first * second;
		printf("%lld", result);
	} else if (strcmp(operationType, "subtraction") == 0) {
		printf("Enter the first number: ");
		unsigned long long first, second;
		scanf("%lld", &first);
		printf("Enter the second number: ");
		scanf("%lld", &second);
		unsigned long long result = first - second;
		printf("%lld", result);
	} else if (strcmp(operationType, "division") == 0) {
		printf("If you get incorrect results, it's probably a limit by the way I do it.\n");
		printf("Enter the first number: ");
		unsigned long long first, second;
		scanf("%lld", &first);
		printf("Enter the second number: ");
		scanf("%lld", &second);
		double result = (double)first / second;
		printf("%Lf", result);
	} else {
		printf("Operation type not supported.");
	}
	system("pause > nul"); 
}