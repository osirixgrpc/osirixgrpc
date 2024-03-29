// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: browsercontroller.proto

#include "browsercontroller.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = ::PROTOBUF_NAMESPACE_ID::internal;
namespace osirixgrpc {
template <typename>
PROTOBUF_CONSTEXPR BrowserControllerDatabaseSelectionResponse::BrowserControllerDatabaseSelectionResponse(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.series_)*/{}
  , /*decltype(_impl_.studies_)*/{}
  , /*decltype(_impl_.status_)*/nullptr} {}
struct BrowserControllerDatabaseSelectionResponseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR BrowserControllerDatabaseSelectionResponseDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~BrowserControllerDatabaseSelectionResponseDefaultTypeInternal() {}
  union {
    BrowserControllerDatabaseSelectionResponse _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 BrowserControllerDatabaseSelectionResponseDefaultTypeInternal _BrowserControllerDatabaseSelectionResponse_default_instance_;
template <typename>
PROTOBUF_CONSTEXPR BrowserControllerCopyFilesIfNeededRequest::BrowserControllerCopyFilesIfNeededRequest(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.paths_)*/{}
  , /*decltype(_impl_.browser_)*/nullptr} {}
struct BrowserControllerCopyFilesIfNeededRequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR BrowserControllerCopyFilesIfNeededRequestDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~BrowserControllerCopyFilesIfNeededRequestDefaultTypeInternal() {}
  union {
    BrowserControllerCopyFilesIfNeededRequest _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 BrowserControllerCopyFilesIfNeededRequestDefaultTypeInternal _BrowserControllerCopyFilesIfNeededRequest_default_instance_;
}  // namespace osirixgrpc
static ::_pb::Metadata file_level_metadata_browsercontroller_2eproto[2];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_browsercontroller_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_browsercontroller_2eproto = nullptr;
const ::uint32_t TableStruct_browsercontroller_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) = {
    PROTOBUF_FIELD_OFFSET(::osirixgrpc::BrowserControllerDatabaseSelectionResponse, _impl_._has_bits_),
    PROTOBUF_FIELD_OFFSET(::osirixgrpc::BrowserControllerDatabaseSelectionResponse, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::osirixgrpc::BrowserControllerDatabaseSelectionResponse, _impl_.status_),
    PROTOBUF_FIELD_OFFSET(::osirixgrpc::BrowserControllerDatabaseSelectionResponse, _impl_.series_),
    PROTOBUF_FIELD_OFFSET(::osirixgrpc::BrowserControllerDatabaseSelectionResponse, _impl_.studies_),
    0,
    ~0u,
    ~0u,
    PROTOBUF_FIELD_OFFSET(::osirixgrpc::BrowserControllerCopyFilesIfNeededRequest, _impl_._has_bits_),
    PROTOBUF_FIELD_OFFSET(::osirixgrpc::BrowserControllerCopyFilesIfNeededRequest, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::osirixgrpc::BrowserControllerCopyFilesIfNeededRequest, _impl_.browser_),
    PROTOBUF_FIELD_OFFSET(::osirixgrpc::BrowserControllerCopyFilesIfNeededRequest, _impl_.paths_),
    0,
    ~0u,
};

static const ::_pbi::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        { 0, 11, -1, sizeof(::osirixgrpc::BrowserControllerDatabaseSelectionResponse)},
        { 14, 24, -1, sizeof(::osirixgrpc::BrowserControllerCopyFilesIfNeededRequest)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::osirixgrpc::_BrowserControllerDatabaseSelectionResponse_default_instance_._instance,
    &::osirixgrpc::_BrowserControllerCopyFilesIfNeededRequest_default_instance_._instance,
};
const char descriptor_table_protodef_browsercontroller_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\027browsercontroller.proto\022\nosirixgrpc\032\017u"
    "tilities.proto\032\013types.proto\"\242\001\n*BrowserC"
    "ontrollerDatabaseSelectionResponse\022\"\n\006st"
    "atus\030\001 \001(\0132\022.osirixgrpc.Status\022\'\n\006series"
    "\030\002 \003(\0132\027.osirixgrpc.DicomSeries\022\'\n\007studi"
    "es\030\003 \003(\0132\026.osirixgrpc.DicomStudy\"j\n)Brow"
    "serControllerCopyFilesIfNeededRequest\022.\n"
    "\007browser\030\001 \001(\0132\035.osirixgrpc.BrowserContr"
    "oller\022\r\n\005paths\030\002 \003(\tb\006proto3"
};
static const ::_pbi::DescriptorTable* const descriptor_table_browsercontroller_2eproto_deps[2] =
    {
        &::descriptor_table_types_2eproto,
        &::descriptor_table_utilities_2eproto,
};
static ::absl::once_flag descriptor_table_browsercontroller_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_browsercontroller_2eproto = {
    false,
    false,
    348,
    descriptor_table_protodef_browsercontroller_2eproto,
    "browsercontroller.proto",
    &descriptor_table_browsercontroller_2eproto_once,
    descriptor_table_browsercontroller_2eproto_deps,
    2,
    2,
    schemas,
    file_default_instances,
    TableStruct_browsercontroller_2eproto::offsets,
    file_level_metadata_browsercontroller_2eproto,
    file_level_enum_descriptors_browsercontroller_2eproto,
    file_level_service_descriptors_browsercontroller_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_browsercontroller_2eproto_getter() {
  return &descriptor_table_browsercontroller_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_browsercontroller_2eproto(&descriptor_table_browsercontroller_2eproto);
namespace osirixgrpc {
// ===================================================================

class BrowserControllerDatabaseSelectionResponse::_Internal {
 public:
  using HasBits = decltype(std::declval<BrowserControllerDatabaseSelectionResponse>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
    8 * PROTOBUF_FIELD_OFFSET(BrowserControllerDatabaseSelectionResponse, _impl_._has_bits_);
  static const ::osirixgrpc::Status& status(const BrowserControllerDatabaseSelectionResponse* msg);
  static void set_has_status(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

const ::osirixgrpc::Status&
BrowserControllerDatabaseSelectionResponse::_Internal::status(const BrowserControllerDatabaseSelectionResponse* msg) {
  return *msg->_impl_.status_;
}
void BrowserControllerDatabaseSelectionResponse::clear_status() {
  if (_impl_.status_ != nullptr) _impl_.status_->Clear();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
void BrowserControllerDatabaseSelectionResponse::clear_series() {
  _internal_mutable_series()->Clear();
}
void BrowserControllerDatabaseSelectionResponse::clear_studies() {
  _internal_mutable_studies()->Clear();
}
BrowserControllerDatabaseSelectionResponse::BrowserControllerDatabaseSelectionResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:osirixgrpc.BrowserControllerDatabaseSelectionResponse)
}
BrowserControllerDatabaseSelectionResponse::BrowserControllerDatabaseSelectionResponse(const BrowserControllerDatabaseSelectionResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  BrowserControllerDatabaseSelectionResponse* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.series_){from._impl_.series_}
    , decltype(_impl_.studies_){from._impl_.studies_}
    , decltype(_impl_.status_){nullptr}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if ((from._impl_._has_bits_[0] & 0x00000001u) != 0) {
    _this->_impl_.status_ = new ::osirixgrpc::Status(*from._impl_.status_);
  }
  // @@protoc_insertion_point(copy_constructor:osirixgrpc.BrowserControllerDatabaseSelectionResponse)
}

inline void BrowserControllerDatabaseSelectionResponse::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.series_){arena}
    , decltype(_impl_.studies_){arena}
    , decltype(_impl_.status_){nullptr}
  };
}

BrowserControllerDatabaseSelectionResponse::~BrowserControllerDatabaseSelectionResponse() {
  // @@protoc_insertion_point(destructor:osirixgrpc.BrowserControllerDatabaseSelectionResponse)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void BrowserControllerDatabaseSelectionResponse::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _internal_mutable_series()->~RepeatedPtrField();
  _internal_mutable_studies()->~RepeatedPtrField();
  if (this != internal_default_instance()) delete _impl_.status_;
}

void BrowserControllerDatabaseSelectionResponse::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void BrowserControllerDatabaseSelectionResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:osirixgrpc.BrowserControllerDatabaseSelectionResponse)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _internal_mutable_series()->Clear();
  _internal_mutable_studies()->Clear();
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    ABSL_DCHECK(_impl_.status_ != nullptr);
    _impl_.status_->Clear();
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* BrowserControllerDatabaseSelectionResponse::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .osirixgrpc.Status status = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_status(), ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // repeated .osirixgrpc.DicomSeries series = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_series(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
        } else {
          goto handle_unusual;
        }
        continue;
      // repeated .osirixgrpc.DicomStudy studies = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 26)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_studies(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<26>(ptr));
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _impl_._has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* BrowserControllerDatabaseSelectionResponse::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:osirixgrpc.BrowserControllerDatabaseSelectionResponse)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // .osirixgrpc.Status status = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, _Internal::status(this),
        _Internal::status(this).GetCachedSize(), target, stream);
  }

  // repeated .osirixgrpc.DicomSeries series = 2;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_series_size()); i < n; i++) {
    const auto& repfield = this->_internal_series(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(2, repfield, repfield.GetCachedSize(), target, stream);
  }

  // repeated .osirixgrpc.DicomStudy studies = 3;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_studies_size()); i < n; i++) {
    const auto& repfield = this->_internal_studies(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(3, repfield, repfield.GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:osirixgrpc.BrowserControllerDatabaseSelectionResponse)
  return target;
}

::size_t BrowserControllerDatabaseSelectionResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:osirixgrpc.BrowserControllerDatabaseSelectionResponse)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .osirixgrpc.DicomSeries series = 2;
  total_size += 1UL * this->_internal_series_size();
  for (const auto& msg : this->_internal_series()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // repeated .osirixgrpc.DicomStudy studies = 3;
  total_size += 1UL * this->_internal_studies_size();
  for (const auto& msg : this->_internal_studies()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // .osirixgrpc.Status status = 1;
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.status_);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData BrowserControllerDatabaseSelectionResponse::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    BrowserControllerDatabaseSelectionResponse::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*BrowserControllerDatabaseSelectionResponse::GetClassData() const { return &_class_data_; }


void BrowserControllerDatabaseSelectionResponse::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<BrowserControllerDatabaseSelectionResponse*>(&to_msg);
  auto& from = static_cast<const BrowserControllerDatabaseSelectionResponse&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:osirixgrpc.BrowserControllerDatabaseSelectionResponse)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_internal_mutable_series()->MergeFrom(from._internal_series());
  _this->_internal_mutable_studies()->MergeFrom(from._internal_studies());
  if ((from._impl_._has_bits_[0] & 0x00000001u) != 0) {
    _this->_internal_mutable_status()->::osirixgrpc::Status::MergeFrom(
        from._internal_status());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void BrowserControllerDatabaseSelectionResponse::CopyFrom(const BrowserControllerDatabaseSelectionResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:osirixgrpc.BrowserControllerDatabaseSelectionResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool BrowserControllerDatabaseSelectionResponse::IsInitialized() const {
  return true;
}

void BrowserControllerDatabaseSelectionResponse::InternalSwap(BrowserControllerDatabaseSelectionResponse* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  _internal_mutable_series()->InternalSwap(other->_internal_mutable_series());
  _internal_mutable_studies()->InternalSwap(other->_internal_mutable_studies());
  swap(_impl_.status_, other->_impl_.status_);
}

::PROTOBUF_NAMESPACE_ID::Metadata BrowserControllerDatabaseSelectionResponse::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_browsercontroller_2eproto_getter, &descriptor_table_browsercontroller_2eproto_once,
      file_level_metadata_browsercontroller_2eproto[0]);
}
// ===================================================================

class BrowserControllerCopyFilesIfNeededRequest::_Internal {
 public:
  using HasBits = decltype(std::declval<BrowserControllerCopyFilesIfNeededRequest>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
    8 * PROTOBUF_FIELD_OFFSET(BrowserControllerCopyFilesIfNeededRequest, _impl_._has_bits_);
  static const ::osirixgrpc::BrowserController& browser(const BrowserControllerCopyFilesIfNeededRequest* msg);
  static void set_has_browser(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

const ::osirixgrpc::BrowserController&
BrowserControllerCopyFilesIfNeededRequest::_Internal::browser(const BrowserControllerCopyFilesIfNeededRequest* msg) {
  return *msg->_impl_.browser_;
}
void BrowserControllerCopyFilesIfNeededRequest::clear_browser() {
  if (_impl_.browser_ != nullptr) _impl_.browser_->Clear();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
BrowserControllerCopyFilesIfNeededRequest::BrowserControllerCopyFilesIfNeededRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest)
}
BrowserControllerCopyFilesIfNeededRequest::BrowserControllerCopyFilesIfNeededRequest(const BrowserControllerCopyFilesIfNeededRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  BrowserControllerCopyFilesIfNeededRequest* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.paths_){from._impl_.paths_}
    , decltype(_impl_.browser_){nullptr}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if ((from._impl_._has_bits_[0] & 0x00000001u) != 0) {
    _this->_impl_.browser_ = new ::osirixgrpc::BrowserController(*from._impl_.browser_);
  }
  // @@protoc_insertion_point(copy_constructor:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest)
}

inline void BrowserControllerCopyFilesIfNeededRequest::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.paths_){arena}
    , decltype(_impl_.browser_){nullptr}
  };
}

BrowserControllerCopyFilesIfNeededRequest::~BrowserControllerCopyFilesIfNeededRequest() {
  // @@protoc_insertion_point(destructor:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void BrowserControllerCopyFilesIfNeededRequest::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _internal_mutable_paths()->~RepeatedPtrField();
  if (this != internal_default_instance()) delete _impl_.browser_;
}

void BrowserControllerCopyFilesIfNeededRequest::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void BrowserControllerCopyFilesIfNeededRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _internal_mutable_paths()->Clear();
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    ABSL_DCHECK(_impl_.browser_ != nullptr);
    _impl_.browser_->Clear();
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* BrowserControllerCopyFilesIfNeededRequest::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .osirixgrpc.BrowserController browser = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_browser(), ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // repeated string paths = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_paths();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _impl_._has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* BrowserControllerCopyFilesIfNeededRequest::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // .osirixgrpc.BrowserController browser = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, _Internal::browser(this),
        _Internal::browser(this).GetCachedSize(), target, stream);
  }

  // repeated string paths = 2;
  for (int i = 0, n = this->_internal_paths_size(); i < n; ++i) {
    const auto& s = this->_internal_paths(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
        s.data(), static_cast<int>(s.length()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE, "osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths");
    target = stream->WriteString(2, s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest)
  return target;
}

::size_t BrowserControllerCopyFilesIfNeededRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated string paths = 2;
  total_size += 1 * ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_internal_paths().size());
  for (int i = 0, n = _internal_paths().size(); i < n; ++i) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        _internal_paths().Get(i));
  }

  // .osirixgrpc.BrowserController browser = 1;
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.browser_);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData BrowserControllerCopyFilesIfNeededRequest::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    BrowserControllerCopyFilesIfNeededRequest::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*BrowserControllerCopyFilesIfNeededRequest::GetClassData() const { return &_class_data_; }


void BrowserControllerCopyFilesIfNeededRequest::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<BrowserControllerCopyFilesIfNeededRequest*>(&to_msg);
  auto& from = static_cast<const BrowserControllerCopyFilesIfNeededRequest&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_internal_mutable_paths()->MergeFrom(from._internal_paths());
  if ((from._impl_._has_bits_[0] & 0x00000001u) != 0) {
    _this->_internal_mutable_browser()->::osirixgrpc::BrowserController::MergeFrom(
        from._internal_browser());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void BrowserControllerCopyFilesIfNeededRequest::CopyFrom(const BrowserControllerCopyFilesIfNeededRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool BrowserControllerCopyFilesIfNeededRequest::IsInitialized() const {
  return true;
}

void BrowserControllerCopyFilesIfNeededRequest::InternalSwap(BrowserControllerCopyFilesIfNeededRequest* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  _internal_mutable_paths()->InternalSwap(
      other->_internal_mutable_paths());
  swap(_impl_.browser_, other->_impl_.browser_);
}

::PROTOBUF_NAMESPACE_ID::Metadata BrowserControllerCopyFilesIfNeededRequest::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_browsercontroller_2eproto_getter, &descriptor_table_browsercontroller_2eproto_once,
      file_level_metadata_browsercontroller_2eproto[1]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace osirixgrpc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::osirixgrpc::BrowserControllerDatabaseSelectionResponse*
Arena::CreateMaybeMessage< ::osirixgrpc::BrowserControllerDatabaseSelectionResponse >(Arena* arena) {
  return Arena::CreateMessageInternal< ::osirixgrpc::BrowserControllerDatabaseSelectionResponse >(arena);
}
template<> PROTOBUF_NOINLINE ::osirixgrpc::BrowserControllerCopyFilesIfNeededRequest*
Arena::CreateMaybeMessage< ::osirixgrpc::BrowserControllerCopyFilesIfNeededRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::osirixgrpc::BrowserControllerCopyFilesIfNeededRequest >(arena);
}
PROTOBUF_NAMESPACE_CLOSE
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"
