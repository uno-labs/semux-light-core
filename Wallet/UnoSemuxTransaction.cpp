#include "UnoSemuxTransaction.hpp"

namespace UnoSemux {

UnoSemuxTransaction::UnoSemuxTransaction (void) noexcept
{
}

UnoSemuxTransaction::UnoSemuxTransaction (const UnoSemuxTransaction& aTransaction):
iNetworkType(aTransaction.iNetworkType),
iType(aTransaction.iType),
iAddrTo(aTransaction.iAddrTo),
iValue(aTransaction.iValue),
iFee(aTransaction.iFee),
iNonce(aTransaction.iNonce),
iTimestamp(aTransaction.iTimestamp),
iData(aTransaction.iData),
iGas(aTransaction.iGas),
iGasPrice(aTransaction.iGasPrice)
{
}

UnoSemuxTransaction::UnoSemuxTransaction (UnoSemuxTransaction&& aTransaction) noexcept:
iNetworkType(std::move(aTransaction.iNetworkType)),
iType(std::move(aTransaction.iType)),
iAddrTo(std::move(aTransaction.iAddrTo)),
iValue(std::move(aTransaction.iValue)),
iFee(std::move(aTransaction.iFee)),
iNonce(std::move(aTransaction.iNonce)),
iTimestamp(std::move(aTransaction.iTimestamp)),
iData(std::move(aTransaction.iData)),
iGas(std::move(aTransaction.iGas)),
iGasPrice(std::move(aTransaction.iGasPrice))
{
}

UnoSemuxTransaction::UnoSemuxTransaction (const NetworkTypeTE		aNetworkType,
										  const TransactionTypeTE	aType,
										  const GpBytesArray&		aAddrTo,
										  const nanosem_t			aValue,
										  const nanosem_t			aFee,
										  const s_int_64			aNonce,
										  const unix_ts_ms_t		aTimestamp,
										  const GpBytesArray&		aData,
										  const semgas_t			aGas,
										  const nanosem_t			aGasPrice):
iNetworkType(aNetworkType),
iType(aType),
iAddrTo(aAddrTo),
iValue(aValue),
iFee(aFee),
iNonce(aNonce),
iTimestamp(aTimestamp),
iData(aData),
iGas(aGas),
iGasPrice(aGasPrice)
{
}

UnoSemuxTransaction::UnoSemuxTransaction (const NetworkTypeTE		aNetworkType,
										  const TransactionTypeTE	aType,
										  GpBytesArray&&			aAddrTo,
										  const nanosem_t			aValue,
										  const nanosem_t			aFee,
										  const s_int_64			aNonce,
										  const unix_ts_ms_t		aTimestamp,
										  GpBytesArray&&			aData,
										  const semgas_t			aGas,
										  const nanosem_t			aGasPrice) noexcept:
iNetworkType(aNetworkType),
iType(aType),
iAddrTo(std::move(aAddrTo)),
iValue(aValue),
iFee(aFee),
iNonce(aNonce),
iTimestamp(std::move(aTimestamp)),
iData(aData),
iGas(aGas),
iGasPrice(aGasPrice)
{
}

UnoSemuxTransaction::~UnoSemuxTransaction (void) noexcept
{
}

GpBytesArray	UnoSemuxTransaction::Encode (void) const
{
	GpBytesArray res;
	res.reserve(64 + iData.size());

	GpByteOStreamByteArray ostream(res);

	ostream.UInt8(u_int_8(iNetworkType));
	ostream.UInt8(u_int_8(iType));
	ostream.CompactSInt32(NumOps::SConvert<s_int_32>(iAddrTo.size()));
	ostream.Bytes(iAddrTo);
	ostream.SInt64(iValue.ValueAs<s_int_64>());
	ostream.SInt64(iFee.ValueAs<s_int_64>());
	ostream.SInt64(iNonce);
	ostream.SInt64(iTimestamp.ValueAs<s_int_64>());
	ostream.CompactSInt32(NumOps::SConvert<s_int_32>(iData.size()));
	ostream.Bytes(iData);

	if (   (iType == TransactionTypeT::CALL)
		|| (iType == TransactionTypeT::CREATE))
	{
		ostream.SInt64(iGas.ValueAs<s_int_64>());
		ostream.SInt64(iGasPrice.ValueAs<s_int_64>());
	}

	return res;
}

}//namespace UnoSemux