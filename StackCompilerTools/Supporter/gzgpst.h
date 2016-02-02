/*
 * gzgpst.h
 */

#ifndef __GZ_GPST_H__
#define __GZ_GPST_H__


//#ifdef __cplusplus
extern "C" {
//#endif

unsigned int wgtochina_lb(int wg_flag,  unsigned int wg_lng, unsigned int wg_lat, int wg_heit, int wg_week,
								  unsigned int wg_time,  unsigned int *china_lng, unsigned int *china_lat);

//#ifdef __cplusplus
} /* extern "C" */
//#endif

#endif
