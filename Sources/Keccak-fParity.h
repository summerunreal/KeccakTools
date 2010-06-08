/*
Tools for the Keccak sponge function family.
Authors: Guido Bertoni, Joan Daemen, Michaël Peeters and Gilles Van Assche

This code is hereby put in the public domain. It is given as is,
without any guarantee.

For more information, feedback or questions, please refer to our website:
http://keccak.noekeon.org/
*/

#ifndef _KECCAKFPARITY_H_
#define _KECCAKFPARITY_H_

#include "Keccak-fParts.h"

/** The PackedParity type is one 64-bit word, containing up to 8 5-bit
  * parities, coming from up to 8 slices. The parity of slice z is
  * in the bits corresponding to (0-31)*32^z in the word.
  * See getPackedParityFromParity() and getParityFromPackedParity() for more details.
  */
typedef UINT64 PackedParity;

/** This function returns a PackedParity with bits set to zero, except for parity at
  * slice z, with a given value.
  * @param   parity     The parity of the slice with z-coordinate @a z.
  * @param   z          The z-coordinate.
  * @return A value of type PackedParity with the given parity.
  */
inline PackedParity getPackedParityFromParity(const RowValue& parity, const unsigned int& z)
{
    return (PackedParity)parity << (5*z);
}

/** This function returns the parity value at slice z in the given PackedParity value.
  * @param   parity     The parity to read from.
  * @param   z          The z-coordinate to read from.
  * @return The parity of the slice with z-coordinate @a z.
  */
inline RowValue getParityFromPackedParity(const PackedParity& parity, const unsigned int& z)
{
    return (parity >> (5*z)) & 0x1F;
}

/** This function converts from a vector of parity of each slice
  * to a PackedParity value. 
  * @param   parity     The parity of a state as vector of row values.
  * @return The parity of a state as a PackedParity value.
  */
PackedParity packParity(const vector<RowValue>& parity);

/** This function converts from a PackedParity value 
  * to a vector of parity of each slice. 
  * @param   packedParity   The parity of a state as a PackedParity value.
  * @param   parity         The parity of a state as a vector of row values.
  * @param   laneSize       The number of slices.
  */
void unpackParity(PackedParity packedParity, vector<RowValue>& parity, unsigned int laneSize);

/** This function computes the parity of a slice.
  * @param   slice  The value of a slice.
  * @return The parity of the given slice value.
  */
RowValue getParity(SliceValue slice);

/** This function computes the parity of a state, and returns it in a
  * PackedParity.
  * @param   state  The value of the state given as a vector of slices.
  * @return The parity of the state.
  */
PackedParity getParity(const vector<SliceValue>& state);

/** This function computes the parity of a state, slice per slice,
  * and returns it in a vector of row values.
  * @param   state  The value of the state given as a vector of slices.
  * @param   parity The parity of @a state as a vector of row values.
  */
void getParity(const vector<SliceValue>& state, vector<RowValue>& parity);

/** This function computes the parity of a state, sheet per sheet, 
  * and returns it in a vector of lane values.
  * @param   state  The value of the state given as a vector of lanes.
  * @param   parity The parity of @a state as a vector of 5 lane values.
  */
void getParity(const vector<LaneValue>& state, vector<LaneValue>& parity);

/** This function converts the parity of a state 
  * expressed as a vector of parities of each slice
  * into a vector of parities of each sheet.
  * @param   paritySlices   The parity as a vector of rows.
  * @param   paritySheets   The parity as a vector of lanes.
  */
void fromSlicesToSheetsParity(const vector<RowValue>& paritySlices, vector<LaneValue>& paritySheets);

/** This function converts the parity of a state
  * expressed as a vector of parities of each sheet
  * into a vector of parities of each slice.
  * @pre @a paritySlices must be initialized with the correct size (lane size).
  * @param   paritySheets   The parity as a vector of lanes.
  * @param   paritySlices   The parity as a vector of rows.
  */
void fromSheetsToSlicesParity(const vector<LaneValue>& paritySheets, vector<RowValue>& paritySlices);

#endif