
#include <unistd.h>

#include <stdio.h>

#include <sys/socket.h>

#include <stdlib.h>

#include <netinet/in.h>

#include <string.h>

#include <netinet/tcp.h>

#include <time.h>

#include <unistd.h>

#include <stdlib.h>



#define BILLION  1000000000L


#define MPORT        60000  /* ftHgÌ|[g         */

#define MSTARTCODE   0xAA   /* JnR[h                 */

#define MENDCODE     0x55   /* I¹R[h                 */

#define MLENGBUFFER  1024   /* f[^obt@[·         */

#define MNOTRANSMAX  6      /* `                     */

#define MSTCODEOFLAST 0xBB  /* ÅãÌMÌJnR[h     */

#define MENCODEOFLAST 0xCC  /* ÅãÌVOiÌI¹R[h */



int main(int nargc, char const *aargv[])

{

  int nnorunmax   = 100 ;	/* ÀsÌÅå         */

  int ntotalbyte  = 100 ;       /* M³êœoCg */

  int nmaxtimeval = 0;          /* ÅåMÔ         */

  int nmintimeval = 0;          /* Å¬MÔ         */

  /* üÍp[^[ðmF·é */

  if(nargc >= 3)

  {

    nnorunmax = atoi(aargv[1]);

    ntotalbyte = atoi(aargv[2]);

  }

  int nsizedata = ntotalbyte / sizeof(int);

  /* SocketÌéŸÆúÏ */

  int nserverfd  = 0;

  int nnewsocket = 0;

  int nsockopt   = 1;

  int ntmp       = 0;

  int ntmp1       = 0;

  int ntotaltime = 0;

  char abuffer[MLENGBUFFER] = {0};

  char aipslave[INET_ADDRSTRLEN];

  struct sockaddr_in straddress;

  int naddrlen = sizeof(straddress);

  struct sockaddr_in* stripslave = (struct sockaddr_in*) &straddress;

  /* f[^zñðú»·é */

  int ndata[1000] = {};

  ndata[0] = MSTARTCODE;

  ndata[1] = 1;

  ndata[2] = 1;

  ndata[3] = nsizedata;

  ndata[nsizedata - 1] = MENDCODE;

 

  /* ^C~OvZÌœßÌéŸÆúÏ */

  struct timeval strstatime, strendtime;

  struct timeval strstatime1, strendtime1;



  int nelapsetime[1000] = {};

  int nelapsetimeFull[4000] = {};

  int nelapsetimeClock[1000] = {};

  int nelapsetimeClockTime[1000] = {};

  struct timespec start, stop;



  long ltime     = 0, ltime1 = 0;

  long lsecs     = 0, lsecs1 = 0;

  long lusecs    = 0, lusecs1 = 0;

  int nvalread   = -1;

  int nretcode   = 0;

  /* Socketì¬ */

  if((nserverfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)

  {

    printf("Socketì¬G[\n");

    return -1;

  }

  /* SocketÝè */

  if(setsockopt(nserverfd, SOL_SOCKET, SO_REUSEADDR , &nsockopt, sizeof(nsockopt)))

  {

    printf("SocketÝèG[\n");

    return -2;

  }

  nsockopt = 1;

  if(setsockopt(nserverfd, IPPROTO_TCP, TCP_NODELAY , &nsockopt, sizeof(nsockopt)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }



  straddress.sin_family = AF_INET;

  straddress.sin_addr.s_addr = INADDR_ANY;

  straddress.sin_port = htons(MPORT);

  /* [JAhXðSocketÉÖAt¯Ü· */

  if(bind(nserverfd, (struct sockaddr *) &straddress, sizeof(straddress)) < 0)

  {

    printf("SocketAhXÝèG[\n");

    return -3;

  }

  /* SocketÍMÚ±ðbXµÄ¢Ü· */

  if(listen(nserverfd, 3) < 0)

  {

    printf("SocketListenG[\n");

    return -4;

  }

  /* SocketÅÌMÚ±sðÂµÜ· */

  if((nnewsocket = accept(nserverfd, (struct sockaddr *) &straddress,(socklen_t*) &naddrlen)) < 0)

  {

    printf("SocketAcceptG[\n");

    return -5;

  }

  nsockopt = 1;

  if(setsockopt(nserverfd, IPPROTO_TCP, TCP_NODELAY , &nsockopt, sizeof(nsockopt)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

#if 0

  int ttt = 100;

  setsockopt(nnewsocket, SOL_SOCKET, SO_SNDBUFFORCE , &ttt, sizeof(int));

  setsockopt(nnewsocket, SOL_SOCKET, SO_RCVBUFFORCE , &ttt, sizeof(int));

#endif



  while(ndata[2] <= nnorunmax)

  {

    ndata[1] = 1;

    /* MÅÌf[^pbP[WÚsÌ^C~OvZðJn */   

    clock_gettime( CLOCK_MONOTONIC  , &start);

    clock_t tStart = clock();

    gettimeofday(&strstatime, NULL);

    while(ndata[1] <= MNOTRANSMAX)

    {

      /* abufferÌf[^ðndataÉèÄé */

      memcpy(&abuffer[0], &ndata, ntotalbyte);

      gettimeofday(&strstatime1, NULL);



  nsockopt = 1;

  if(setsockopt(nnewsocket, IPPROTO_TCP, TCP_NODELAY , &nsockopt, sizeof(nsockopt)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

#if 0

  nsockopt = 1;

  if(setsockopt(nnewsocket, IPPROTO_TCP, TCP_CORK , &nsockopt, sizeof(nsockopt)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

  nsockopt = 0;

  if(setsockopt(nnewsocket, IPPROTO_TCP, TCP_CORK , &nsockopt, sizeof(nsockopt)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

#endif



  nsockopt = 1;

  if(setsockopt(nnewsocket, IPPROTO_TCP, TCP_QUICKACK  , &nsockopt, sizeof(nsockopt)))

  {

    printf("Socket設定エラー333\n");

    return -2;

  }



      send(nnewsocket , abuffer, ntotalbyte, 0);

      /* Slave©çf[^MðóMµAabufferÉÛ¶ */

#if 0

  nsockopt = 1;

  if(setsockopt(nnewsocket, IPPROTO_TCP, TCP_CORK , &nsockopt, sizeof(nsockopt)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

  nsockopt = 0;

  if(setsockopt(nnewsocket, IPPROTO_TCP, TCP_CORK , &nsockopt, sizeof(nsockopt)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }

#endif

  nsockopt = 1;

  if(setsockopt(nnewsocket, IPPROTO_TCP, TCP_NODELAY , &nsockopt, sizeof(nsockopt)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }



  nsockopt = 1;

  if(setsockopt(nnewsocket, IPPROTO_TCP, TCP_QUICKACK  , &nsockopt, sizeof(nsockopt)))

  {

    printf("Socket設定エラー333\n");

    return -2;

  }

  nsockopt = 1;



      nvalread = recv(nnewsocket, abuffer, ntotalbyte, 0);



  nsockopt = 1;

  if(setsockopt(nnewsocket, IPPROTO_TCP, TCP_QUICKACK  , &nsockopt, sizeof(nsockopt)))

  {

    printf("Socket設定エラー333\n");

    return -2;

  }

  nsockopt = 1;

  if(setsockopt(nnewsocket, IPPROTO_TCP, TCP_NODELAY , &nsockopt, sizeof(nsockopt)))

  {

    printf("Socket設定エラー222\n");

    return -2;

  }



      if(nvalread < ntotalbyte)

      {

        nretcode = -6;

        printf("SocketóÌG[\n");

        break;

      }

      else

      {

        gettimeofday(&strendtime1, NULL);

        lsecs1  = strendtime1.tv_sec  - strstatime1.tv_sec;

        lusecs1 = strendtime1.tv_usec - strstatime1.tv_usec;

        nelapsetimeFull[ntmp1++] = ((lsecs1) * 1000000 + lusecs1);



        /* ndataÌf[^ðabufferÉèÄé */

        memcpy(&ndata, &abuffer[0], ntotalbyte);

        /* bZW[ðâ· */

        ndata[1]++;



        if((ndata[1] >= (MNOTRANSMAX - 1)) && (ndata[2] == nnorunmax))       

        {

          ndata[0] = MSTCODEOFLAST;

          ndata[nsizedata - 1] = MENCODEOFLAST;

        }

        else if(((ndata[0] != MSTARTCODE) || (ndata[nsizedata - 1] != MENDCODE)))

        {

          nretcode = -7;

          printf("Jn©I¹R[hG[\n");

          break;

        }

      }

    }

    

    /* MÅÌf[^pbP[WÈ~Ì^C~OvZÌI¹ */

    gettimeofday(&strendtime, NULL);

    clock_t tEnd = clock();

    clock_gettime( CLOCK_MONOTONIC  , &stop);

    float tClockTime = ((float)(tEnd - tStart) / CLOCKS_PER_SEC)*1000000;

    float ttime = (stop.tv_sec - start.tv_sec)*1000000 + (stop.tv_nsec-start.tv_nsec )/ 1000;



    nelapsetimeClock[ntmp] = (int)tClockTime;

    nelapsetimeClockTime[ntmp] = (int)(ttime);

    ndata[2]++;

    /* ÔìðvZ·é */

    lsecs  = strendtime.tv_sec  - strstatime.tv_sec;

    lusecs = strendtime.tv_usec - strstatime.tv_usec;

    nelapsetime[ntmp++] = ((lsecs) * 1000000 + lusecs);

    //usleep(1000);

  }

  /* printf("Result of %d times measure with size of data is %d bytes: \n", nnorunmax, ntotalbyte); */

  nmintimeval = nelapsetime[0];

  ntmp1 = 0;

  int tmpTotal = 0;

  for(ntmp = 0; ntmp < nnorunmax; ntmp++)

  {

    if(nelapsetime[ntmp] > nmaxtimeval)

    {

      nmaxtimeval = nelapsetime[ntmp];

    }

    else if(nelapsetime[ntmp] < nmintimeval)

    {

      nmintimeval = nelapsetime[ntmp];

    }

    tmpTotal = nelapsetimeFull[ntmp1]+nelapsetimeFull[ntmp1+1]+nelapsetimeFull[ntmp1+2];

    /* printf("%d: %d,%d,%d--%d,%d,%d:%d\n", ntmp, nelapsetime[ntmp], nelapsetimeClock[ntmp],nelapsetimeClockTime[ntmp],nelapsetimeFull[ntmp1++],nelapsetimeFull[ntmp1++],nelapsetimeFull[ntmp1++], tmpTotal); */

    printf("%d: %d\n", ntmp, nelapsetime[ntmp]);

    ntotaltime += nelapsetime[ntmp];

  }

  printf("\n\nAverage time: %.2f [us] (microseconds)", (float)ntotaltime / nnorunmax);

  printf("\nMaximum time: %d", nmaxtimeval);

  printf("\nMinimum time: %d\n", nmintimeval); 

  close(nnewsocket);

  return nretcode;

}
