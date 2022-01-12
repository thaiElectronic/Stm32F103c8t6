#include "lib_sd.h" 

FRESULT res;


/*******************************************************************************
	* @T�n ch?c nang 		: scan_files
	* @M� t? ch?c nang	: T�m ki?m t?t c? c�c t?p trong thu m?c t?p
	* @Input						: tham s? du?ng d?n: thu m?c g?c
	* @Output 					: Kh�ng c�
	* @Return 					: Tham s? FRESULT
	* @Notes						: Kh�ng c�
  *****************************************************************************/
FRESULT scan_files (
    char* path        /* N�t b?t d?u du?c qu�t (c�n du?c s? d?ng nhu khu v?c l�m vi?c) */
)
{
    FRESULT res;
    FILINFO fno;
    DIR dir;
    int i;
    char *fn;   			/* H�m n�y gi? s? cfg kh�ng ph?i Unicode. */
#if _USE_LFN
    static char lfn[_MAX_LFN + 1];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif


    res = f_opendir(&dir, path);          								 /* M? thu m?c */
    if (res == FR_OK) {
        i = strlen(path);
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* �?c m?t m?c thu m?c */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Ng?t do l?i ho?c k?t th�c c?a dir */
            if (fno.fname[0] == '.') continue;             /* B? qua m?c nh?p d?u ch?m */
#if _USE_LFN
            fn = *fno.lfname ? fno.lfname : fno.fname;
#else
            fn = fno.fname;
#endif
            if (fno.fattrib & AM_DIR) {                    /* N?u n� l� m?t thu m?c */
                sprintf(&path[i], "/%s", fn);
								printf("scan file - %s\n\r",path);
                res = scan_files(path);
                if (res != FR_OK) break;
                path[i] = 0;
            } else {                                       /* N?u n� l� m?t t?p tin. */
                printf("scan file - %s/%s\n\r", path, fn);
            }
        }
    }else{
		printf("scan files error : %d\n\r",res);
	}

    return res;
}

/*******************************************************************************
	* @T�n Ch?c nang		: SD_TotalSize
	* @M� t? ch?c nang	: Kh�ng gian t?p chi?m d?ng 
	* @Input						: Kh�ng c�
	* @Output						: Kh�ng c�
	* @Return 					: tham s? 1: Th�nh c�ng,0: th?t b?i															
	* @Notes   					: Kh�ng c�
  *****************************************************************************/

int SD_TotalSize(char *path)
{
    FATFS *fs;
    DWORD fre_clust;        

    res = f_getfree(path, &fre_clust, &fs);  /* Ph?i l� thu m?c g?c */
    if ( res==FR_OK ) 
    {
	  printf("\n\rget %s drive space.\n\r",path);
	  /* In dung lu?ng tr?ng theo don v? MB (gi? s? 512 byte / sector) */
      printf("%d MB total drive space.\r\n"
           "%d MB available.\r\n",
           ( (fs->n_fatent - 2) * fs->csize ) / 2 /1024 , (fre_clust * fs->csize) / 2 /1024 );
		
	  return 1;
	}
	else
	{ 
	  printf("\n\rGet total drive space faild!\n\r");
	  return 0;   
	}
}

/*******************************************************************************
	* @T�n ch?c nang 		: Delay
	* @M� t? ch?c nang 	: Nh?n ra ch?c nang tr� ho�n
	* @Tham s? 					: Tham s? th?i gian tr?
	* @Input 						: nCount(Gi� tr? c�ng l?n th� th?i gian tr? c�ng d�i)
	* @Output						: Kh�ng c�
	* @Return						: Kh�ng c�
	* @Notes						: Kh�ng c�
  *****************************************************************************/
void  Delay (uint32_t nCount){

  for(; nCount != 0; nCount--);
}
