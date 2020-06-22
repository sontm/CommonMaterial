

#include <stdio.h>

#include <sys/socket.h>

#include <stdlib.h>

#include <netinet/in.h>

#include <string.h>

#include <netinet/tcp.h>

#include <time.h>

#include <unistd.h>

#include <stdlib.h>



/* àéŸ */

#define MPORT          60000             /* ftHgÌ|[g         */

#define MSTARTCODE     0xAA              /* JnR[h                 */

#define MENDCODE       0x55              /* I¹R[h                 */

#define MLENGBUFFER    1024              /* f[^obt@[·	       */

#define MNOTRANSMAX    6                 /* `                     */

#define MGAMENSERVERIP "192.168.50.131"     /* æÊT[oAhX         */

#define MSTCODEOFLAST  0xBB              /* ÅãÌMÌJnR[h     */

#define MENCODEOFLAST  0xCC              /* ÅãÌVOiÌI¹R[h */



int main(int nargc, char const *aargv[])

{

  int nsizedata = 1024;	             /* f[^TCYðú»·é */

  int nfinishstatus = 1;             /* f[^]I¹Xe[^X */

				     /* 1 : Mð±¯é         */

                                     /* 0 : MðI¹           */					 



  /* SocketÌéŸÆúÏ */

  int nsocket = 0;

  struct sockaddr_in strmasteraddr;

  char abuffer[MLENGBUFFER] = {0};

  int nvalread = -1;

  int nretcode = 0;

  int nsockopt2 = 1;

  int ndata[MLENGBUFFER] = {};

  struct timeval strstatime, strendtime;

  /* Socketì¬·é */

  if((nsocket = socket(AF_INET, SOCK_STREAM , 0)) < 0)

  {

    printf("Socketì¬G[\n");

    return -1;

  }



  memset(&strmasteraddr, '0', sizeof(strmasteraddr));

  strmasteraddr.sin_family = AF_INET;

  strmasteraddr.sin_port = htons(MPORT);             /* MPORTÚ±ðÇÁ */

  /* IPv4AhXðeLXg©çoCi`®ÉÏ··é */

  if(inet_pton(AF_INET,MGAMENSERVERIP, &strmasteraddr.sin_addr) <= 0)

  {

    printf("SocketAhXÝèG[\n");

    return -2;

  }

  /* SLAVEÍMASTERÌAhXÉÚ±µÜ· */

  if(connect(nsocket, (struct sockaddr *)&strmasteraddr, sizeof(strmasteraddr)) < 0)

  {

    printf("SocketConnectG[\n");

    return -3;

  }

  ndata[2] = 0;

#if 0

  int ttt = 100;

  setsockopt(nsocket, SOL_SOCKET, SO_SNDBUFFORCE , &ttt, sizeof(int));

  setsockopt(nsocket, SOL_SOCKET, SO_RCVBUFFORCE , &ttt, sizeof(int));

#endif

  while(nfinishstatus)               /* I¹Xe[^XªMðI¹·éÌðÒÁÄ¢Ü·  */

  {

    ndata[1] = 1;

    while(ndata[1] < MNOTRANSMAX) 

    {

      /* Master©çf[^MðóMµAabufferÉÛ¶ */

  nsockopt2 = 1;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_QUICKACK  , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー333\n");

    return -2;

  }

  nsockopt2 = 1;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_NODELAY , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

#if 0

  nsockopt2 = 1;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_CORK , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

  nsockopt2 = 0;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_CORK , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

#endif

      nvalread = recv(nsocket, abuffer, (nsizedata * sizeof(int)), 0);



  nsockopt2 = 1;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_QUICKACK  , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー333\n");

    return -2;

  }

  nsockopt2 = 1;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_NODELAY , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

#if 0

  nsockopt2 = 1;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_CORK , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

  nsockopt2 = 0;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_CORK , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

#endif

      if(nvalread < 0)

      {

        printf("SocketóÌG[\n");

        nretcode = -4;

        break;

      }

      else

      {

        /* ndataÌf[^ðabufferÉèÄé */

        memcpy(&ndata, &abuffer[0], nsizedata * sizeof(int));

        nsizedata = ndata[3];

        if((ndata[0] == MSTCODEOFLAST) && (ndata[nsizedata - 1] == MENCODEOFLAST))

        {

          ndata[1]++;

          /* abufferÌf[^ðndataÉèÄé */

          memcpy(&abuffer[0], &ndata, nsizedata * sizeof(int));

          send(nsocket , abuffer, nsizedata * sizeof(int), 0);

          nfinishstatus = 0;

          break;

        }

        else if((ndata[0] != MSTARTCODE) || (ndata[nsizedata - 1]) != MENDCODE)

        {

          nretcode = -5;

          printf("Jn©I¹R[hG[\n");

          break;

        }

        /* bZW[ðâ· */

        ndata[1]++;

        /* abufferÌf[^ðndataÉèÄé */

        memcpy(&abuffer[0], &ndata, nsizedata * sizeof(int));



  nsockopt2 = 1;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_NODELAY , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

#if 0

  nsockopt2 = 1;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_CORK , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

  nsockopt2 = 0;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_CORK , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

#endif

        send(nsocket , abuffer, nsizedata * sizeof(int), 0);



#if 0

  nsockopt2 = 1;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_CORK , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

  nsockopt2 = 0;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_CORK , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

#endif

#if 1

  nsockopt2 = 1;

  if(setsockopt(nsocket, IPPROTO_TCP, TCP_NODELAY , &nsockopt2, sizeof(nsockopt2)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

#endif



      }

    }

  }

  int testL = 0;

  int arrElap[1000] = {0};

  int arrElapC[1000] = {0};

  long lsecs, lusecs;

  struct timespec start, stop;

  for (testL = 0; testL < 0; testL++) {

	gettimeofday(&strstatime, NULL);

	long begin = (strstatime.tv_sec) * 1000000 + (strstatime.tv_usec) ;

	clock_gettime( CLOCK_MONOTONIC  , &start);





	clock_gettime( CLOCK_MONOTONIC  , &stop);

	gettimeofday(&strendtime, NULL);

	long end = (strendtime.tv_sec) * 1000000 + (strendtime.tv_usec) ;



	lsecs  = strendtime.tv_sec  - strstatime.tv_sec;

    	lusecs = strendtime.tv_usec - strstatime.tv_usec;

	arrElap[testL] = end-begin;

	float ttime = (stop.tv_sec - start.tv_sec)*1000000 + (stop.tv_nsec-start.tv_nsec )/ 1000;

	arrElapC[testL] = ttime;

  }

  for (testL = 0; testL < 0; testL++) {

	printf("%d: %d, %d\n", testL, arrElap[testL], arrElapC[testL]);

  }

  close(nsocket);

  return nretcode;

}
