#ifndef ERRTYPE_H_
#define ERRTYPE_H_

typedef enum{
	OK				,
	NOK				,
	NULL_POINTER	,
	RTC_OK      	,
	RTC_ERROR    	,
	RTC_BUSY   		,
	RTC_TIMEOUT 
  
}ErrorState_t;

typedef enum
{
  FLASH_OK       = 0x00U,
  FLASH_ERROR    = 0x01U,
  FLASH_BUSY     = 0x02U,
  FLASH_TIMEOUT  = 0x03U

}FLASH_ErrorState_t;


#define NULL ((void *)0)

#endif
