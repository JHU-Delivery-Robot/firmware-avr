#ifndef _BIT_UTIL_H_
#define _BIT_UTIL_H_


// Bit field manipulation tools
/**
 * Convert a value to a register field using the library declared psoition and
 * offset
 */
#define _VAL2FLD(field, value) (((uint8_t)(value) << field ## _bp) & field ## _bm)
/**
 * Extract the value from a field of a register using the mask and affset
 * technique
 */
#define _FLD2VAL(field, value) (((uint8_t)(value) & field ## _bm) >> field ## _bp)

// Read-Modify-Write operations. Prefer special set/clr/toggle regs where
// possible to reduce cycle count
#define _SET_BIT(var, pos) var |= 1 << pos
#define _CLR_BIT(var, pos) var &= ~(1 << pos)
#define _INV_BIT(var, pos) var ^= 1 << pos

/**
 * Clear a multi-bit field in a register
 */
#define _FLDCLR(reg, field) (reg &= ~(field ## _bm << field ## _bp))
/**
 * Set the value of a register field if it has been zeroed before
 */
#define _FLDSET(reg, field, val) (reg |= ((val & field ## _bm) << field ## _bp))

#endif /* _BIT_UTIL_H_ */
