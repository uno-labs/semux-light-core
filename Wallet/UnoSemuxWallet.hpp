#pragma once

#include "UnoSemuxAddrsGroup.hpp"

namespace UnoSemux {

class UNOSEMUXLIGHTCORE_API UnoSemuxWallet
{
public:
	CLASS_REMOVE_CTRS_EXCEPT_DEFAULT(UnoSemuxWallet)
	CLASS_DECLARE_DEFAULTS(UnoSemuxWallet)

	using HDAddrGroupsT = UnoSemuxAddrsGroup::C::MapCountT::SP;

public:
								UnoSemuxWallet		(void);
								~UnoSemuxWallet		(void) noexcept;

	void						Clear				(void) noexcept;
	void						Set					(UnoSemuxWallet&& aWallet) noexcept;

	UnoSemuxAddr::SP			GenRndAddr			(void);
	UnoSemuxAddr::SP			GenNextHDAddr		(const count_t aHDGroupId);
	UnoSemuxAddr::SP			GenHDAddr			(const count_t aHDGroupId, const count_t aAddrId);
	void						DeleteAddr			(GpRawPtrCharR aAddrStrHex);
	UnoSemuxAddr::SP			FindAddr			(GpRawPtrCharR aAddrStrHex);
	count_t						AddHDGroup			(GpRawPtrCharR aMnemonic, GpRawPtrCharR aPassword);
	void						DeleteHDGroup		(const count_t aHDGroupId);

	const UnoSemuxAddrsGroup&	RndAddrGroup		(void) const noexcept {return iRndAddrGroup;}
	const HDAddrGroupsT&		HDAddrGroups		(void) const noexcept {return iHDAddrGroups;}
	count_t						HDAddrGroupLastId	(void) const noexcept {return iHDAddrGroupLastId;}

	GpBytesArray				Serialize			(GpRawPtrCharR aPassword) const;
	std::string					SerializeHex		(GpRawPtrCharR aPassword) const;

	void						Deserialize			(GpRawPtrByteR aData, GpRawPtrCharR aPassword);
	void						DeserializeHex		(GpRawPtrCharR aDataStrHex, GpRawPtrCharR aPassword);

private:
	UnoSemuxAddrsGroup			iRndAddrGroup;
	HDAddrGroupsT				iHDAddrGroups;
	count_t						iHDAddrGroupLastId = 0_cnt;
};

}//UnoSemux
