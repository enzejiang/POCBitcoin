// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Transaction.proto

#include "Transaction.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

extern PROTOBUF_INTERNAL_EXPORT_TxIn_2eproto ::google::protobuf::internal::SCCInfo<1> scc_info_TxIn_TxIn_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_TxOut_2eproto ::google::protobuf::internal::SCCInfo<0> scc_info_TxOut_TxOut_2eproto;
namespace Enze {
class TransactionDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<Transaction> _instance;
} _Transaction_default_instance_;
}  // namespace Enze
static void InitDefaultsTransaction_Transaction_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Enze::_Transaction_default_instance_;
    new (ptr) ::Enze::Transaction();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Enze::Transaction::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<2> scc_info_Transaction_Transaction_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 2, InitDefaultsTransaction_Transaction_2eproto}, {
      &scc_info_TxIn_TxIn_2eproto.base,
      &scc_info_TxOut_TxOut_2eproto.base,}};

void InitDefaults_Transaction_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_Transaction_Transaction_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_Transaction_2eproto[1];
constexpr ::google::protobuf::EnumDescriptor const** file_level_enum_descriptors_Transaction_2eproto = nullptr;
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_Transaction_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_Transaction_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Enze::Transaction, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Enze::Transaction, ncurversion_),
  PROTOBUF_FIELD_OFFSET(::Enze::Transaction, nlocktime_),
  PROTOBUF_FIELD_OFFSET(::Enze::Transaction, vtxin_),
  PROTOBUF_FIELD_OFFSET(::Enze::Transaction, vtxout_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::Enze::Transaction)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::Enze::_Transaction_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_Transaction_2eproto = {
  {}, AddDescriptors_Transaction_2eproto, "Transaction.proto", schemas,
  file_default_instances, TableStruct_Transaction_2eproto::offsets,
  file_level_metadata_Transaction_2eproto, 1, file_level_enum_descriptors_Transaction_2eproto, file_level_service_descriptors_Transaction_2eproto,
};

::google::protobuf::internal::DescriptorTable descriptor_table_Transaction_2eproto = {
  false, InitDefaults_Transaction_2eproto, 
  "\n\021Transaction.proto\022\004Enze\032\nTxIn.proto\032\013T"
  "xOut.proto\"m\n\013Transaction\022\023\n\013nCurVersion"
  "\030\001 \001(\005\022\021\n\tnLockTime\030\002 \001(\005\022\031\n\005vTxIn\030\003 \003(\013"
  "2\n.Enze.TxIn\022\033\n\006vTxOut\030\004 \003(\0132\013.Enze.TxOu"
  "tb\006proto3"
,
  "Transaction.proto", &assign_descriptors_table_Transaction_2eproto, 169,
};

void AddDescriptors_Transaction_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[2] =
  {
    ::AddDescriptors_TxIn_2eproto,
    ::AddDescriptors_TxOut_2eproto,
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_Transaction_2eproto, deps, 2);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_Transaction_2eproto = []() { AddDescriptors_Transaction_2eproto(); return true; }();
namespace Enze {

// ===================================================================

void Transaction::InitAsDefaultInstance() {
}
class Transaction::HasBitSetters {
 public:
};

void Transaction::clear_vtxin() {
  vtxin_.Clear();
}
void Transaction::clear_vtxout() {
  vtxout_.Clear();
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Transaction::kNCurVersionFieldNumber;
const int Transaction::kNLockTimeFieldNumber;
const int Transaction::kVTxInFieldNumber;
const int Transaction::kVTxOutFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Transaction::Transaction()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Enze.Transaction)
}
Transaction::Transaction(const Transaction& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      vtxin_(from.vtxin_),
      vtxout_(from.vtxout_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&ncurversion_, &from.ncurversion_,
    static_cast<size_t>(reinterpret_cast<char*>(&nlocktime_) -
    reinterpret_cast<char*>(&ncurversion_)) + sizeof(nlocktime_));
  // @@protoc_insertion_point(copy_constructor:Enze.Transaction)
}

void Transaction::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_Transaction_Transaction_2eproto.base);
  ::memset(&ncurversion_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&nlocktime_) -
      reinterpret_cast<char*>(&ncurversion_)) + sizeof(nlocktime_));
}

Transaction::~Transaction() {
  // @@protoc_insertion_point(destructor:Enze.Transaction)
  SharedDtor();
}

void Transaction::SharedDtor() {
}

void Transaction::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Transaction& Transaction::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_Transaction_Transaction_2eproto.base);
  return *internal_default_instance();
}


void Transaction::Clear() {
// @@protoc_insertion_point(message_clear_start:Enze.Transaction)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  vtxin_.Clear();
  vtxout_.Clear();
  ::memset(&ncurversion_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&nlocktime_) -
      reinterpret_cast<char*>(&ncurversion_)) + sizeof(nlocktime_));
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* Transaction::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<Transaction*>(object);
  ::google::protobuf::uint32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ::google::protobuf::uint32 tag;
    ptr = Varint::Parse32Inline(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // int32 nCurVersion = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        ::google::protobuf::uint64 val;
        ptr = Varint::Parse64(ptr, &val);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ::google::protobuf::int32 value = val;
        msg->set_ncurversion(value);
        break;
      }
      // int32 nLockTime = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 16) goto handle_unusual;
        ::google::protobuf::uint64 val;
        ptr = Varint::Parse64(ptr, &val);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ::google::protobuf::int32 value = val;
        msg->set_nlocktime(value);
        break;
      }
      // repeated .Enze.TxIn vTxIn = 3;
      case 3: {
        if (static_cast<::google::protobuf::uint8>(tag) != 26) goto handle_unusual;
        do {
          ptr = Varint::Parse32Inline(ptr, &size);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
          parser_till_end = ::Enze::TxIn::_InternalParse;
          object = msg->add_vtxin();
          if (size > end - ptr) goto len_delim_till_end;
          auto newend = ptr + size;
          bool ok = ctx->ParseExactRange({parser_till_end, object},
                                         ptr, newend);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ok);
          ptr = newend;
          if (ptr >= end) break;
        } while ((::google::protobuf::io::UnalignedLoad<::google::protobuf::uint64>(ptr) & 255) == 26 && (ptr += 1));
        break;
      }
      // repeated .Enze.TxOut vTxOut = 4;
      case 4: {
        if (static_cast<::google::protobuf::uint8>(tag) != 34) goto handle_unusual;
        do {
          ptr = Varint::Parse32Inline(ptr, &size);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
          parser_till_end = ::Enze::TxOut::_InternalParse;
          object = msg->add_vtxout();
          if (size > end - ptr) goto len_delim_till_end;
          auto newend = ptr + size;
          bool ok = ctx->ParseExactRange({parser_till_end, object},
                                         ptr, newend);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ok);
          ptr = newend;
          if (ptr >= end) break;
        } while ((::google::protobuf::io::UnalignedLoad<::google::protobuf::uint64>(ptr) & 255) == 34 && (ptr += 1));
        break;
      }
      default: {
      handle_unusual: (void)&&handle_unusual;
        if ((tag & 7) == 4 || tag == 0) {
          bool ok = ctx->ValidEndGroup(tag);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ok);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
len_delim_till_end: (void)&&len_delim_till_end;
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                                 {parser_till_end, object}, size);
group_continues: (void)&&group_continues;
  GOOGLE_DCHECK(ptr >= end);
  ctx->StoreGroup({_InternalParse, msg}, {parser_till_end, object}, depth);
  return ptr;
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool Transaction::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Enze.Transaction)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 nCurVersion = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &ncurversion_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 nLockTime = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (16 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &nlocktime_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .Enze.TxIn vTxIn = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (26 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
                input, add_vtxin()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .Enze.TxOut vTxOut = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (34 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
                input, add_vtxout()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Enze.Transaction)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Enze.Transaction)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void Transaction::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Enze.Transaction)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 nCurVersion = 1;
  if (this->ncurversion() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->ncurversion(), output);
  }

  // int32 nLockTime = 2;
  if (this->nlocktime() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->nlocktime(), output);
  }

  // repeated .Enze.TxIn vTxIn = 3;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->vtxin_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3,
      this->vtxin(static_cast<int>(i)),
      output);
  }

  // repeated .Enze.TxOut vTxOut = 4;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->vtxout_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4,
      this->vtxout(static_cast<int>(i)),
      output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Enze.Transaction)
}

::google::protobuf::uint8* Transaction::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Enze.Transaction)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 nCurVersion = 1;
  if (this->ncurversion() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->ncurversion(), target);
  }

  // int32 nLockTime = 2;
  if (this->nlocktime() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->nlocktime(), target);
  }

  // repeated .Enze.TxIn vTxIn = 3;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->vtxin_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        3, this->vtxin(static_cast<int>(i)), deterministic, target);
  }

  // repeated .Enze.TxOut vTxOut = 4;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->vtxout_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        4, this->vtxout(static_cast<int>(i)), deterministic, target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Enze.Transaction)
  return target;
}

size_t Transaction::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Enze.Transaction)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .Enze.TxIn vTxIn = 3;
  {
    unsigned int count = static_cast<unsigned int>(this->vtxin_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSize(
          this->vtxin(static_cast<int>(i)));
    }
  }

  // repeated .Enze.TxOut vTxOut = 4;
  {
    unsigned int count = static_cast<unsigned int>(this->vtxout_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSize(
          this->vtxout(static_cast<int>(i)));
    }
  }

  // int32 nCurVersion = 1;
  if (this->ncurversion() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->ncurversion());
  }

  // int32 nLockTime = 2;
  if (this->nlocktime() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->nlocktime());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Transaction::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Enze.Transaction)
  GOOGLE_DCHECK_NE(&from, this);
  const Transaction* source =
      ::google::protobuf::DynamicCastToGenerated<Transaction>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Enze.Transaction)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Enze.Transaction)
    MergeFrom(*source);
  }
}

void Transaction::MergeFrom(const Transaction& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Enze.Transaction)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  vtxin_.MergeFrom(from.vtxin_);
  vtxout_.MergeFrom(from.vtxout_);
  if (from.ncurversion() != 0) {
    set_ncurversion(from.ncurversion());
  }
  if (from.nlocktime() != 0) {
    set_nlocktime(from.nlocktime());
  }
}

void Transaction::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Enze.Transaction)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Transaction::CopyFrom(const Transaction& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Enze.Transaction)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Transaction::IsInitialized() const {
  return true;
}

void Transaction::Swap(Transaction* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Transaction::InternalSwap(Transaction* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  CastToBase(&vtxin_)->InternalSwap(CastToBase(&other->vtxin_));
  CastToBase(&vtxout_)->InternalSwap(CastToBase(&other->vtxout_));
  swap(ncurversion_, other->ncurversion_);
  swap(nlocktime_, other->nlocktime_);
}

::google::protobuf::Metadata Transaction::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_Transaction_2eproto);
  return ::file_level_metadata_Transaction_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Enze
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::Enze::Transaction* Arena::CreateMaybeMessage< ::Enze::Transaction >(Arena* arena) {
  return Arena::CreateInternal< ::Enze::Transaction >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
