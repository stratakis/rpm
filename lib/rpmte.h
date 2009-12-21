#ifndef H_RPMTE
#define H_RPMTE

/** \ingroup rpmts rpmte
 * \file lib/rpmte.h
 * Structures used for an "rpmte" transaction element.
 */

#include <rpm/rpmtypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 */
extern int _rpmte_debug;

/** \ingroup rpmte
 * Transaction element ordering chain linkage.
 */
typedef struct tsortInfo_s *		tsortInfo;

/** \ingroup rpmte
 * Transaction element type.
 */
typedef enum rpmElementType_e {
    TR_ADDED		= (1 << 0),	/*!< Package will be installed. */
    TR_REMOVED		= (1 << 1)	/*!< Package will be removed. */
} rpmElementType;

/** \ingroup rpmte
 * Destroy a transaction element.
 * @param te		transaction element
 * @return		NULL always
 */
rpmte rpmteFree(rpmte te);

/** \ingroup rpmte
 * Create a transaction element.
 * @param ts		unused
 * @param h		header
 * @param type		TR_ADDED/TR_REMOVED
 * @param key		(TR_ADDED) package retrieval key (e.g. file name)
 * @param relocs	(TR_ADDED) package file relocations
 * @param dboffset	unused
 * @return		new transaction element
 */
rpmte rpmteNew(const rpmts ts, Header h, rpmElementType type,
		fnpyKey key,
		rpmRelocation * relocs,
		int dboffset);

/** \ingroup rpmte
 * Retrieve header from transaction element.
 * @param te		transaction element
 * @return		header
 */
Header rpmteHeader(rpmte te);

/** \ingroup rpmte
 * Save header into transaction element.
 * @param te		transaction element
 * @param h		header
 * @return		NULL always
 */
Header rpmteSetHeader(rpmte te, Header h);

/** \ingroup rpmte
 * Retrieve type of transaction element.
 * @param te		transaction element
 * @return		type
 */
rpmElementType rpmteType(rpmte te);

/** \ingroup rpmte
 * Retrieve name string of transaction element.
 * @param te		transaction element
 * @return		name string
 */
const char * rpmteN(rpmte te);

/** \ingroup rpmte
 * Retrieve epoch string of transaction element.
 * @param te		transaction element
 * @return		epoch string
 */
const char * rpmteE(rpmte te);

/** \ingroup rpmte
 * Retrieve version string of transaction element.
 * @param te		transaction element
 * @return		version string
 */
const char * rpmteV(rpmte te);

/** \ingroup rpmte
 * Retrieve release string of transaction element.
 * @param te		transaction element
 * @return		release string
 */
const char * rpmteR(rpmte te);

/** \ingroup rpmte
 * Retrieve arch string of transaction element.
 * @param te		transaction element
 * @return		arch string
 */
const char * rpmteA(rpmte te);

/** \ingroup rpmte
 * Retrieve os string of transaction element.
 * @param te		transaction element
 * @return		os string
 */
const char * rpmteO(rpmte te);

/** \ingroup rpmte
 * Retrieve isSource attribute of transaction element.
 * @param te		transaction element
 * @return		isSource attribute
 */
int rpmteIsSource(rpmte te);

/** \ingroup rpmte
 * Retrieve color bits of transaction element.
 * @param te		transaction element
 * @return		color bits
 */
rpm_color_t rpmteColor(rpmte te);

/** \ingroup rpmte
 * Set color bits of transaction element.
 * @param te		transaction element
 * @param color		new color bits
 * @return		previous color bits
 */
rpm_color_t rpmteSetColor(rpmte te, rpm_color_t color);

/** \ingroup rpmte
 * Retrieve last instance installed to the database.
 * @param te		transaction element
 * @return		last install instance.
 */
unsigned int rpmteDBInstance(rpmte te);

/** \ingroup rpmte
 * Set last instance installed to the database.
 * @param te		transaction element
 * @param instance	Database instance of last install element.
 * @return		last install instance.
 */
void rpmteSetDBInstance(rpmte te, unsigned int instance);

/** \ingroup rpmte
 * Retrieve size in bytes of package file.
 * @todo Signature header is estimated at 256b.
 * @param te		transaction element
 * @return		size in bytes of package file.
 */
rpm_loff_t rpmtePkgFileSize(rpmte te);

/** \ingroup rpmte
 * Retrieve parent transaction element.
 * @param te		transaction element
 * @return		parent transaction element
 */
rpmte rpmteParent(rpmte te);

/** \ingroup rpmte
 * Set parent transaction element.
 * @param te		transaction element
 * @param pte		new parent transaction element
 * @return		previous parent transaction element
 */
rpmte rpmteSetParent(rpmte te, rpmte pte);

/** \ingroup rpmte
 * Destroy dependency set info of transaction element.
 * @param te		transaction element
 */
void rpmteCleanDS(rpmte te);

/** \ingroup rpmte
 * Set dependent element of TR_REMOVED transaction element.
 * @param te		transaction element
 * @param depends       dependent transaction element
 */
void rpmteSetDependsOn(rpmte te, rpmte depends);

/** \ingroup rpmte
 * Retrieve dependent element of TR_REMOVED transaction element.
 * @param te		transaction element
 * @return		dependent transaction element
 */
rpmte rpmteDependsOn(rpmte te);

/** \ingroup rpmte
 * Retrieve rpmdb instance of TR_REMOVED transaction element.
 * @param te		transaction element
 * @return		rpmdb instance
 */
int rpmteDBOffset(rpmte te);

/** \ingroup rpmte
 * Retrieve [epoch:]version-release string from transaction element.
 * @param te		transaction element
 * @return		[epoch:]version-release string
 */
const char * rpmteEVR(rpmte te);

/** \ingroup rpmte
 * Retrieve name-[epoch:]version-release string from transaction element.
 * @param te		transaction element
 * @return		name-[epoch:]version-release string
 */
const char * rpmteNEVR(rpmte te);

/** \ingroup rpmte
 * Retrieve name-[epoch:]version-release.arch string from transaction element.
 * @param te		transaction element
 * @return		name-[epoch:]version-release.arch string
 */
const char * rpmteNEVRA(rpmte te);

/** \ingroup rpmte
 * Retrieve key from transaction element.
 * @param te		transaction element
 * @return		key
 */
fnpyKey rpmteKey(rpmte te);

/** \ingroup rpmte
 * Return failed status of transaction element.
 * @param te		transaction element
 * @return		1 if transaction element (or its parents) failed
 */
int rpmteFailed(rpmte te);

/** \ingroup rpmte
 * Retrieve dependency tag set from transaction element.
 * @param te		transaction element
 * @param tag		dependency tag
 * @return		dependency tag set
 */
rpmds rpmteDS(rpmte te, rpmTag tag);

/** \ingroup rpmte
 * Retrieve file info tag set from transaction element.
 * @param te		transaction element
 * @return		file info tag set
 */
rpmfi rpmteFI(rpmte te);

/** \ingroup rpmte
 * Calculate transaction element dependency colors/refs from file info.
 * @param te		transaction element
 * @param tag		dependency tag (RPMTAG_PROVIDENAME, RPMTAG_REQUIRENAME)
 */
void rpmteColorDS(rpmte te, rpmTag tag);

#ifdef __cplusplus
}
#endif

#endif	/* H_RPMTE */
