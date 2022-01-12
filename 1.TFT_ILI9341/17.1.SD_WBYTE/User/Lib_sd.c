#include "lib_sd.h" 

FRESULT res;


/*******************************************************************************
	* @Tên ch?c nang 		: scan_files
	* @Mô t? ch?c nang	: Tìm ki?m t?t c? các t?p trong thu m?c t?p
	* @Input						: tham s? du?ng d?n: thu m?c g?c
	* @Output 					: Không có
	* @Return 					: Tham s? FRESULT
	* @Notes						: Không có
  *****************************************************************************/
FRESULT scan_files (
    char* path        /* Nút b?t d?u du?c quét (còn du?c s? d?ng nhu khu v?c làm vi?c) */
)
{
    FRESULT res;
    FILINFO fno;
    DIR dir;
    int i;
    char *fn;   			/* Hàm này gi? s? cfg không ph?i Unicode. */
#if _USE_LFN
    static char lfn[_MAX_LFN + 1];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif


    res = f_opendir(&dir, path);          								 /* M? thu m?c */
    if (res == FR_OK) {
        i = strlen(path);
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Ð?c m?t m?c thu m?c */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Ng?t do l?i ho?c k?t thúc c?a dir */
            if (fno.fname[0] == '.') continue;             /* B? qua m?c nh?p d?u ch?m */
#if _USE_LFN
            fn = *fno.lfname ? fno.lfname : fno.fname;
#else
            fn = fno.fname;
#endif
            if (fno.fattrib & AM_DIR) {                    /* N?u nó là m?t thu m?c */
                sprintf(&path[i], "/%s", fn);
								printf("scan file - %s\n\r",path);
                res = scan_files(path);
                if (res != FR_OK) break;
                path[i] = 0;
            } else {                                       /* N?u nó là m?t t?p tin. */
                printf("scan file - %s/%s\n\r", path, fn);
            }
        }
    }else{
		printf("scan files error : %d\n\r",res);
	}

    return res;
}

/*******************************************************************************
	* @Tên Ch?c nang		: SD_TotalSize
	* @Mô t? ch?c nang	: Không gian t?p chi?m d?ng 
	* @Input						: Không có
	* @Output						: Không có
	* @Return 					: tham s? 1: Thành công,0: th?t b?i															
	* @Notes   					: Không có
  *****************************************************************************/

int SD_TotalSize(char *path)
{
    FATFS *fs;
    DWORD fre_clust;        

    res = f_getfree(path, &fre_clust, &fs);  /* Ph?i là thu m?c g?c */
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
	* @Tên ch?c nang 		: Delay
	* @Mô t? ch?c nang 	: Nh?n ra ch?c nang trì hoãn
	* @Tham s? 					: Tham s? th?i gian tr?
	* @Input 						: nCount(Giá tr? càng l?n thì th?i gian tr? càng dài)
	* @Output						: Không có
	* @Return						: Không có
	* @Notes						: Không có
  *****************************************************************************/
void  Delay (uint32_t nCount){

  for(; nCount != 0; nCount--);
}
