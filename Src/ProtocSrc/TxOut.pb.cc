// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: TxOut.proto

#include "TxOut.pb.h"

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

namespace Enze {
class TxOutDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<TxOut> _instance;
} _TxOut_default_instance_;
}  // namespace Enze
static void InitDefaultsTxOut_TxOut_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Enze::_TxOut_default_instance_;
    new (ptr) ::Enze::TxOut();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Enze::TxOut::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_TxOut_TxOut_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsTxOut_TxOut_2eproto}, {}};

void InitDefaults_TxOut_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_TxOut_TxOut_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_TxOut_2eproto[1];
constexpr ::google::protobuf::EnumDescriptor const** file_level_enum_descriptors_TxOut_2eproto = nullptr;
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_TxOut_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_TxOut_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Enze::TxOut, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Enze::TxOut, nvalue_),
  PROTOBUF_FIELD_OFFSET(::Enze::TxOut, cscriptpubkey_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::Enze::TxOut)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::Enze::_TxOut_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_TxOut_2eproto = {
  {}, AddDescriptors_TxOut_2eproto, "TxOut.proto", schemas,
  file_default_instances, TableStruct_TxOut_2eproto::offsets,
  file_level_metadata_TxOut_2eproto, 1, file_level_enum_descriptors_TxOut_2eproto, file_level_service_descriptors_TxOut_2eproto,
};

::google::protobuf::internal::DescriptorTable descriptor_table_TxOut_2eproto = {
  false, InitDefaults_TxOut_2eproto, 
  "\n\013TxOut.proto\022\004Enze\".\n\005TxOut\022\016\n\006nValue\030\001"
  " \001(\003\022\025\n\rcScriptPubKey\030\002 \001(\tb\006proto3"
,
  "TxOut.proto", &assign_descriptors_table_TxOut_2eproto, 75,
};

void AddDescriptors_TxOut_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[1] =
  {
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_TxOut_2eproto, deps, 0);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_TxOut_2eproto = []() { AddDescriptors_TxOut_2eproto(); return true; }();
namespace Enze {

// ===================================================================

void TxOut::InitAsDefaultInstance() {
}
class TxOut::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int TxOut::kNValueFieldNumber;
const int TxOut::kCScriptPubKeyFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

TxOut::TxOut()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Enze.TxOut)
}
TxOut::TxOut(const TxOut& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  cscriptpubkey_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.cscriptpubkey().size() > 0) {
    cscriptpubkey_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.cscriptpubkey_);
  }
  nvalue_ = from.nvalue_;
  // @@protoc_insertion_point(copy_constructor:Enze.TxOut)
}

void TxOut::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_TxOut_TxOut_2eproto.base);
  cscriptpubkey_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  nvalue_ = PROTOBUF_LONGLONG(0);
}

TxOut::~TxOut() {
  // @@protoc_insertion_point(destructor:Enze.TxOut)
  SharedDtor();
}

void TxOut::SharedDtor() {
  cscriptpubkey_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void TxOut::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const TxOut& TxOut::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_TxOut_TxOut_2eproto.base);
  return *internal_default_instance();
}


void TxOut::Clear() {
// @@protoc_insertion_point(message_clear_start:Enze.TxOut)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cscriptpubkey_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  nvalue_ = PROTOBUF_LONGLONG(0);
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* TxOut::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<TxOut*>(object);
  ::google::protobuf::uint32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ::google::protobuf::uint32 tag;
    ptr = Varint::Parse32Inline(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // int64 nValue = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        ::google::protobuf::uint64 val;
        ptr = Varint::Parse64(ptr, &val);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ::google::protobuf::int64 value = val;
        msg->set_nvalue(value);
        break;
      }
      // string cScriptPubKey = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 18) goto handle_unusual;
        ptr = Varint::Parse32Inline(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ctx->extra_parse_data().SetFieldName("Enze.TxOut.cScriptPubKey");
        parser_till_end = ::google::protobuf::internal::StringParserUTF8;
        ::std::string* str = msg->mutable_cscriptpubkey();
        str->clear();
        object = str;
        if (size > end - ptr) goto len_delim_till_end;
        auto newend = ptr + size;
        if (size) ptr = parser_till_end(ptr, newend, object, ctx);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr == newend);
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
bool TxOut::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Enze.TxOut)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int64 nValue = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &nvalue_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string cScriptPubKey = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (18 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_cscriptpubkey()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->cscriptpubkey().data(), static_cast<int>(this->cscriptpubkey().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "Enze.TxOut.cScriptPubKey"));
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
  // @@protoc_insertion_point(parse_success:Enze.TxOut)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Enze.TxOut)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void TxOut::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Enze.TxOut)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 nValue = 1;
  if (this->nvalue() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->nvalue(), output);
  }

  // string cScriptPubKey = 2;
  if (this->cscriptpubkey().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->cscriptpubkey().data(), static_cast<int>(this->cscriptpubkey().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Enze.TxOut.cScriptPubKey");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->cscriptpubkey(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Enze.TxOut)
}

::google::protobuf::uint8* TxOut::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Enze.TxOut)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 nValue = 1;
  if (this->nvalue() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->nvalue(), target);
  }

  // string cScriptPubKey = 2;
  if (this->cscriptpubkey().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->cscriptpubkey().data(), static_cast<int>(this->cscriptpubkey().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Enze.TxOut.cScriptPubKey");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->cscriptpubkey(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Enze.TxOut)
  return target;
}

size_t TxOut::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Enze.TxOut)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string cScriptPubKey = 2;
  if (this->cscriptpubkey().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->cscriptpubkey());
  }

  // int64 nValue = 1;
  if (this->nvalue() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->nvalue());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void TxOut::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Enze.TxOut)
  GOOGLE_DCHECK_NE(&from, this);
  const TxOut* source =
      ::google::protobuf::DynamicCastToGenerated<TxOut>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Enze.TxOut)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Enze.TxOut)
    MergeFrom(*source);
  }
}

void TxOut::MergeFrom(const TxOut& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Enze.TxOut)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.cscriptpubkey().size() > 0) {

    cscriptpubkey_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.cscriptpubkey_);
  }
  if (from.nvalue() != 0) {
    set_nvalue(from.nvalue());
  }
}

void TxOut::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Enze.TxOut)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TxOut::CopyFrom(const TxOut& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Enze.TxOut)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TxOut::IsInitialized() const {
  return true;
}

void TxOut::Swap(TxOut* other) {
  if (other == this) return;
  InternalSwap(other);
}
void TxOut::InternalSwap(TxOut* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  cscriptpubkey_.Swap(&other->cscriptpubkey_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(nvalue_, other->nvalue_);
}

::google::protobuf::Metadata TxOut::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_TxOut_2eproto);
  return ::file_level_metadata_TxOut_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Enze
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::Enze::TxOut* Arena::CreateMaybeMessage< ::Enze::TxOut >(Arena* arena) {
  return Arena::CreateInternal< ::Enze::TxOut >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
