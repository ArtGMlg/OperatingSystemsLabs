#include <pthread.h>
#include <stdio.h>

char alphabet[]="abcdefghijklmnopqrst";

void thread(void *arg)
{
	int k, j;
	if((int)arg == 1 || (int)arg == 3) {
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE , NULL);
	}
	for (k=0; k<21; k++) {
		printf("\033[%d;%d0H\033[1;3%dm",k+1, 2 * (int)arg, 5 - (int)arg);
		for (j=0; j<(int)arg * 2; j++) {
			printf("%c",alphabet[k]);
		}
		printf("\n");

		if(k == 12 && (int)arg == 3) {
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE , NULL);
		pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
		}
		if(k == 15 && (int)arg == 3) {
			pthread_testcancel();
			usleep(1000000 + 750000 * (int)arg);
			pthread_testcancel();
		}
		else {
		usleep(1000000 + 500000 * (3 - (int)arg));
		}
	}
}

void main()
{

	int k;
	int rc;
	pthread_t tid1, tid2, tid3;

	printf("\033[2J\n");
	pthread_create(&tid1, NULL, (void*)thread, (void*)1);
	pthread_create(&tid2, NULL, (void*)thread, (void*)2);
	pthread_create(&tid3, NULL, (void*)thread, (void*)3);

	for (k=0; k<=20; k++) {
		printf("\033[%d;1H\033[1;37m",k+1);
		printf("%c\n",alphabet[k]);
		if(k == 5) {//на 5 шаге
			rc=pthread_cancel(tid1);
			if(rc != 0) {
				printf("\033[25;1H\033[1;34mError: first thread  cancel failed");
			}
			else {
			printf("\033[25;1H\033[1;34mTrying to cancel first thread");
			}
		}
		if(k == 10) {
			rc=pthread_cancel(tid3);
			if(rc != 0) {
				printf("\033[25;1H\033[1;32mError: third thread cancel failed");
			}
			else {
				printf("\033[25;1H\033[1;32mThird thread cancel is successfull");
			}
		}
		usleep(1500000);
	}
}
