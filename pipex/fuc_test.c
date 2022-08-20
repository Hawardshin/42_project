

#include "pipex.h"
#include "./libft/libft.h"
#include <errno.h>
#define BUFSIZE 30

/*pipe함수 첫번째 예제*/
// int main()
// {
//     int fd[2];
//     char buff[BUFSIZE];
//     pid_t   pid;
//     int state;

//     state = pipe(fd);
//     if (state == -1)
//     {
//         puts("pipe_error");
//         exit(1);
//     }
//     pid = fork();

//     if (pid == -1)
//     {
//         puts("fork error");
//         exit(1);
//     }
//     else if (pid == 0)
//     {
//         write(fd[1], "연결성공 \n",30);
//     }
//     else
//     {
//         read(fd[0],buff,BUFSIZE);
//         printf("%s",buff);
//         // write (1, buff,BUFSIZE);
//     }
//     return (0);
// }
/*멀티 프로세싱 파이프 간의 연결을 하나의 파이프 만으로 부모프로세스와 자식 프로세스간의 양방향 통신을 할때 생기는 문제점을 알수가 있다.*/
// int main(int argc, char *argv[])
// {
//     int fd[2];
//     char buffer[BUFSIZE];
//     pid_t pid;
//     int state;

//     state = pipe(fd);
//     if (state == -1)
//     {
//         puts("pipeerror");
//         exit(1);
//     }
//     pid = fork();
//     if (pid == -1)
//     {
//         puts("fork() error");
//         exit(1);
//     }
//     else if (pid == 0)
//     {
//         write(fd[1], "연결 성공!! \n", 25);
//         // sleep(2);
//         read(fd[0],buffer,BUFSIZE);
//         printf("in child process : %s\n\n",buffer);
//     }
//     else
//     {
//         read(fd[0], buffer,BUFSIZE);
//         printf("in parent process : %s\n\n",buffer);
//         write(fd[1],"정말 좋아!!",25);
//         // sleep(2);
//     }
// }
/*양방향 파이프 생성해서 하기 + wait함수 사용해보기, + wait_pid함수 사용해보기*/
// int main(int argc, char *argv[])
// {
// 	int fd1[2],fd2[2];//fd1은 자식에서 부모로 보내는 파이프 용도로 사용 , fd2는 부모에서 자식으로 보내는 용도로 사용
// 	char buffer[BUFSIZE];
// 	int state;
// 	pid_t pid;

// 	if (pipe(fd1) == -1 || pipe(fd2) == -1)
// 	{
// 		puts("pipe() error");
// 		exit(1);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		puts("fork() error");
// 		exit(1);
// 	}
// 	else if (pid == 0)
// 	{
// 		write(fd1[1], "연결 성공 !!!\n", 25);
// 		read(fd2[0], buffer, BUFSIZE);
// 		sleep(1);
// 		printf("output in child process :: %s \n\n",buffer);
// 	}
// 	else
// 	{
// 		// printf("%d",pid);
// 		read(fd1[0],buffer,BUFSIZE);
// 		printf("output in parent process :: %s \n\n",buffer);
// 		write(fd2[1], "정말 좋아!!", 25);
// 		// wait(&state);// 이걸 해줌으로서 좀비 프로세스가 안 된다.
// 		// sleep(1);
// 	}
// 	return (0);
// }

/*dup 함수에서는 fd값을 다르게는 복사를 해주지만 같은 파일 테이블을 가리키고 있다. 굳이 왜 쓰는지는 좀 더 알아보자.
close를 따로 닫아준다를 유의하자.
dup2 함수에서는 두번째 인자가 첫번째 인자의 복제가 된다. 만약 두번째 인자의 fd값이 열려있다면 닫은 후 복제가 된다.
dup2(fd,fd2); 를 하게 되면 fd2값이 fd가 가리키는 파일태이블을 가리키게 된다.
*/
// int main()
// {
// 	int fd[2];
// 	int fd_temp;
// 	char buffer[7];

// 	pipe(fd);
// 	fd_temp = dup(fd[1]);
// 	printf("fd[1]] : %d\nfd_tmp : %d\n",fd[1],fd_temp);
// 	write(fd_temp, "Hello\n", 7);
//     read(fd[0], buffer, 7);
//     printf("%s", buffer);
// }

//dup2 함수
// int main(void)
// {
//     int temp_fd;
//     int fd[2];
//     int fd2[2];
//     char buffer[6];
//     char buffer2[6];

//     pipe(fd);
//     pipe(fd2);
// 	temp_fd = dup2(fd[1], fd2[1]);
//     printf("temp_fd: %d\nfd[1]: %d\nfd2[1]: %d\n", temp_fd, fd[1], fd2[1]);

//     /* fd2[1]에 입력해보기 이렇게 했을 때 fd2[1]의 기능을 아에 잃어버리고 파이프는 fd[1]의 기능을 가지게 된다.
// 	즉 파이프의 입구를 잃어버렸다.*/
//     write(fd2[1], "hello", 6);
//     read(fd[0], buffer, 6);
//     read(fd2[0], buffer2, 6);

//     printf("\nfd[0]: %s\nfd2[0]: %s\n", buffer, buffer2);

//     /* close() 생략 */
// }

/*dup2함수를 활용한 errno값을 가져오기
표준 출력 표준 에러 출력 값들을 가져와서 파일에 넣을 수 있다는 장점이 있다.*/

// int main()
// {
// 	int fd[2];
// 	char buffer[30];

// 	pipe(fd);
// 	dup2(fd[1],2);
// 	perror("ERROR!");
// 	read(fd[0], buffer,30);
// 	printf("%s",buffer);
// }
/* 이 코드를 실행해보면 에러번호에 따른 에러 메세지를 확인 할 수 있다. errono값은 os나 컴파일러에 따라서 갯수와 해석이 틀려진다.*/
// int main()
// {
// 	char *err;
// 	printf("********에러 메세지 ********\n");
// 	for (int i=0; i <= 116; i++)
// 	{
// 		err=strerror(i);
// 		printf("[%d] :: %s\n",i,err);
// 	}
// }

/*access함수를 이용해서 권한이 있으면 0을 반환하고 없다면 -1 을 반환한다.
errno.h를 인클루드 해서 현재 발생한 에러에 대해서 errno값을 가져오고 errno는 새로운 에러가 발생하면 그걸로 갱신이 된다.
*/
// int main()
// {
// 	char *is_txt = "./test.txt";
// 	char *is_exe = "./a.exe";

// 	printf("txt읽기: %d\n", access(is_txt, R_OK));
// 	printf("%s\n", strerror(errno));
//     printf("txt쓰기: %d\n", access(is_txt, W_OK));
// 	printf("%s\n", strerror(errno));
//     printf("txt실행: %d\n", access(is_txt, X_OK));
// 	printf("%s\n", strerror(errno));
//     printf("txt존재: %d\n", access(is_txt, F_OK));
// 	printf("%s\n", strerror(errno));

//     printf("exe읽기: %d\n", access(is_exe, R_OK));
// 	printf("%s\n", strerror(errno));
//     printf("exe쓰기: %d\n", access(is_exe, W_OK));
// 	printf("%s\n", strerror(errno));
//     printf("exe실행: %d\n", access(is_exe, X_OK));
// 	printf("%s\n", strerror(errno));
//     printf("exe존재: %d\n", access(is_exe, F_OK));
// 	printf("%s\n", strerror(errno));
// }

/*execve() 함수 : 여기서 파일을 삭제해 버릴 수 있기 때문에 위험한 함수 라고 볼 수 있다.*/
// int main()
// {
// 	unlink("./pipex.h.gch");
// 	unlink("test.txt");
// }

/* execve() 함수를 사용해서 쉘 에서 사용하는 명령어를 수행 할 수가 있다.
이 함수는 다른 프로그램을 실행하고 본인은 존재하기 때문에 자식 프로세스에서 실행하기 알맞다!
실패한다면 -1을 반환한다.
인자 1. 파일이름 꼭 절대경로나 상대 경로를 지정해줘야만 한다!
인자 2. 메인의 argv와 비슷한 역활을 하나 여기선 argc가 없기 때문에 마지막에 널이 들어있다.
인자 3. key=value 형식의 환경 변수 문자열 배열리스트로 마지막은 NULL이 와야 한다.
		만약 설정된 환경 변수를 사용하려면 environ 전역변수를 그냥 사용한다.
		C 프로그램에서는 environ 이라는 전역 변수가 미리 만들어 있어 이를 통해 환경 변수 목록을 확인할 수 있다.
		다른 곳에서 미리 선언한 상태이므로 extern 문으로 environ 변수를 참조하여 환경 변수 목록을 확인할 수 있다.
		ls, mv와 같은 명령어들은 "/bin"경로에 위치했습니다.
		하지만 wc와 같은 명령어는 "/bin"경로가 아닌 "usr/bin"경로에 위치하였습니다.
		 "/bin"경로의 명령어들을 예외처리하여 경로가 지정되도록 코드를 구현하면 될 것같습니다.

*/

// int main(int argc, char **argv)
// {
//     char *envp[] = {0};

//     execve("/bin/ls", argv, envp);
//     return (0);
// }
