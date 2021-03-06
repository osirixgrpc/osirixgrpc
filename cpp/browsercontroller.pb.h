// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: browsercontroller.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_browsercontroller_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_browsercontroller_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3014000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3014000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "utilities.pb.h"
#include "types.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_browsercontroller_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_browsercontroller_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_browsercontroller_2eproto;
namespace osirixgrpc {
class BrowserControllerCopyFilesIfNeededRequest;
class BrowserControllerCopyFilesIfNeededRequestDefaultTypeInternal;
extern BrowserControllerCopyFilesIfNeededRequestDefaultTypeInternal _BrowserControllerCopyFilesIfNeededRequest_default_instance_;
class BrowserControllerDatabaseSelectionResponse;
class BrowserControllerDatabaseSelectionResponseDefaultTypeInternal;
extern BrowserControllerDatabaseSelectionResponseDefaultTypeInternal _BrowserControllerDatabaseSelectionResponse_default_instance_;
}  // namespace osirixgrpc
PROTOBUF_NAMESPACE_OPEN
template<> ::osirixgrpc::BrowserControllerCopyFilesIfNeededRequest* Arena::CreateMaybeMessage<::osirixgrpc::BrowserControllerCopyFilesIfNeededRequest>(Arena*);
template<> ::osirixgrpc::BrowserControllerDatabaseSelectionResponse* Arena::CreateMaybeMessage<::osirixgrpc::BrowserControllerDatabaseSelectionResponse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace osirixgrpc {

// ===================================================================

class BrowserControllerDatabaseSelectionResponse PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:osirixgrpc.BrowserControllerDatabaseSelectionResponse) */ {
 public:
  inline BrowserControllerDatabaseSelectionResponse() : BrowserControllerDatabaseSelectionResponse(nullptr) {}
  virtual ~BrowserControllerDatabaseSelectionResponse();

  BrowserControllerDatabaseSelectionResponse(const BrowserControllerDatabaseSelectionResponse& from);
  BrowserControllerDatabaseSelectionResponse(BrowserControllerDatabaseSelectionResponse&& from) noexcept
    : BrowserControllerDatabaseSelectionResponse() {
    *this = ::std::move(from);
  }

  inline BrowserControllerDatabaseSelectionResponse& operator=(const BrowserControllerDatabaseSelectionResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline BrowserControllerDatabaseSelectionResponse& operator=(BrowserControllerDatabaseSelectionResponse&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const BrowserControllerDatabaseSelectionResponse& default_instance();

  static inline const BrowserControllerDatabaseSelectionResponse* internal_default_instance() {
    return reinterpret_cast<const BrowserControllerDatabaseSelectionResponse*>(
               &_BrowserControllerDatabaseSelectionResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(BrowserControllerDatabaseSelectionResponse& a, BrowserControllerDatabaseSelectionResponse& b) {
    a.Swap(&b);
  }
  inline void Swap(BrowserControllerDatabaseSelectionResponse* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(BrowserControllerDatabaseSelectionResponse* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline BrowserControllerDatabaseSelectionResponse* New() const final {
    return CreateMaybeMessage<BrowserControllerDatabaseSelectionResponse>(nullptr);
  }

  BrowserControllerDatabaseSelectionResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<BrowserControllerDatabaseSelectionResponse>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const BrowserControllerDatabaseSelectionResponse& from);
  void MergeFrom(const BrowserControllerDatabaseSelectionResponse& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(BrowserControllerDatabaseSelectionResponse* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "osirixgrpc.BrowserControllerDatabaseSelectionResponse";
  }
  protected:
  explicit BrowserControllerDatabaseSelectionResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_browsercontroller_2eproto);
    return ::descriptor_table_browsercontroller_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSeriesFieldNumber = 2,
    kStudiesFieldNumber = 3,
    kStatusFieldNumber = 1,
  };
  // repeated .osirixgrpc.DicomSeries series = 2;
  int series_size() const;
  private:
  int _internal_series_size() const;
  public:
  void clear_series();
  ::osirixgrpc::DicomSeries* mutable_series(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::osirixgrpc::DicomSeries >*
      mutable_series();
  private:
  const ::osirixgrpc::DicomSeries& _internal_series(int index) const;
  ::osirixgrpc::DicomSeries* _internal_add_series();
  public:
  const ::osirixgrpc::DicomSeries& series(int index) const;
  ::osirixgrpc::DicomSeries* add_series();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::osirixgrpc::DicomSeries >&
      series() const;

  // repeated .osirixgrpc.DicomStudy studies = 3;
  int studies_size() const;
  private:
  int _internal_studies_size() const;
  public:
  void clear_studies();
  ::osirixgrpc::DicomStudy* mutable_studies(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::osirixgrpc::DicomStudy >*
      mutable_studies();
  private:
  const ::osirixgrpc::DicomStudy& _internal_studies(int index) const;
  ::osirixgrpc::DicomStudy* _internal_add_studies();
  public:
  const ::osirixgrpc::DicomStudy& studies(int index) const;
  ::osirixgrpc::DicomStudy* add_studies();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::osirixgrpc::DicomStudy >&
      studies() const;

  // .osirixgrpc.Status status = 1;
  bool has_status() const;
  private:
  bool _internal_has_status() const;
  public:
  void clear_status();
  const ::osirixgrpc::Status& status() const;
  ::osirixgrpc::Status* release_status();
  ::osirixgrpc::Status* mutable_status();
  void set_allocated_status(::osirixgrpc::Status* status);
  private:
  const ::osirixgrpc::Status& _internal_status() const;
  ::osirixgrpc::Status* _internal_mutable_status();
  public:
  void unsafe_arena_set_allocated_status(
      ::osirixgrpc::Status* status);
  ::osirixgrpc::Status* unsafe_arena_release_status();

  // @@protoc_insertion_point(class_scope:osirixgrpc.BrowserControllerDatabaseSelectionResponse)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::osirixgrpc::DicomSeries > series_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::osirixgrpc::DicomStudy > studies_;
  ::osirixgrpc::Status* status_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_browsercontroller_2eproto;
};
// -------------------------------------------------------------------

class BrowserControllerCopyFilesIfNeededRequest PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest) */ {
 public:
  inline BrowserControllerCopyFilesIfNeededRequest() : BrowserControllerCopyFilesIfNeededRequest(nullptr) {}
  virtual ~BrowserControllerCopyFilesIfNeededRequest();

  BrowserControllerCopyFilesIfNeededRequest(const BrowserControllerCopyFilesIfNeededRequest& from);
  BrowserControllerCopyFilesIfNeededRequest(BrowserControllerCopyFilesIfNeededRequest&& from) noexcept
    : BrowserControllerCopyFilesIfNeededRequest() {
    *this = ::std::move(from);
  }

  inline BrowserControllerCopyFilesIfNeededRequest& operator=(const BrowserControllerCopyFilesIfNeededRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline BrowserControllerCopyFilesIfNeededRequest& operator=(BrowserControllerCopyFilesIfNeededRequest&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const BrowserControllerCopyFilesIfNeededRequest& default_instance();

  static inline const BrowserControllerCopyFilesIfNeededRequest* internal_default_instance() {
    return reinterpret_cast<const BrowserControllerCopyFilesIfNeededRequest*>(
               &_BrowserControllerCopyFilesIfNeededRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(BrowserControllerCopyFilesIfNeededRequest& a, BrowserControllerCopyFilesIfNeededRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(BrowserControllerCopyFilesIfNeededRequest* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(BrowserControllerCopyFilesIfNeededRequest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline BrowserControllerCopyFilesIfNeededRequest* New() const final {
    return CreateMaybeMessage<BrowserControllerCopyFilesIfNeededRequest>(nullptr);
  }

  BrowserControllerCopyFilesIfNeededRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<BrowserControllerCopyFilesIfNeededRequest>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const BrowserControllerCopyFilesIfNeededRequest& from);
  void MergeFrom(const BrowserControllerCopyFilesIfNeededRequest& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(BrowserControllerCopyFilesIfNeededRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "osirixgrpc.BrowserControllerCopyFilesIfNeededRequest";
  }
  protected:
  explicit BrowserControllerCopyFilesIfNeededRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_browsercontroller_2eproto);
    return ::descriptor_table_browsercontroller_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPathsFieldNumber = 2,
    kBrowserFieldNumber = 1,
  };
  // repeated string paths = 2;
  int paths_size() const;
  private:
  int _internal_paths_size() const;
  public:
  void clear_paths();
  const std::string& paths(int index) const;
  std::string* mutable_paths(int index);
  void set_paths(int index, const std::string& value);
  void set_paths(int index, std::string&& value);
  void set_paths(int index, const char* value);
  void set_paths(int index, const char* value, size_t size);
  std::string* add_paths();
  void add_paths(const std::string& value);
  void add_paths(std::string&& value);
  void add_paths(const char* value);
  void add_paths(const char* value, size_t size);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>& paths() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>* mutable_paths();
  private:
  const std::string& _internal_paths(int index) const;
  std::string* _internal_add_paths();
  public:

  // .osirixgrpc.BrowserController browser = 1;
  bool has_browser() const;
  private:
  bool _internal_has_browser() const;
  public:
  void clear_browser();
  const ::osirixgrpc::BrowserController& browser() const;
  ::osirixgrpc::BrowserController* release_browser();
  ::osirixgrpc::BrowserController* mutable_browser();
  void set_allocated_browser(::osirixgrpc::BrowserController* browser);
  private:
  const ::osirixgrpc::BrowserController& _internal_browser() const;
  ::osirixgrpc::BrowserController* _internal_mutable_browser();
  public:
  void unsafe_arena_set_allocated_browser(
      ::osirixgrpc::BrowserController* browser);
  ::osirixgrpc::BrowserController* unsafe_arena_release_browser();

  // @@protoc_insertion_point(class_scope:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string> paths_;
  ::osirixgrpc::BrowserController* browser_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_browsercontroller_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// BrowserControllerDatabaseSelectionResponse

// .osirixgrpc.Status status = 1;
inline bool BrowserControllerDatabaseSelectionResponse::_internal_has_status() const {
  return this != internal_default_instance() && status_ != nullptr;
}
inline bool BrowserControllerDatabaseSelectionResponse::has_status() const {
  return _internal_has_status();
}
inline const ::osirixgrpc::Status& BrowserControllerDatabaseSelectionResponse::_internal_status() const {
  const ::osirixgrpc::Status* p = status_;
  return p != nullptr ? *p : reinterpret_cast<const ::osirixgrpc::Status&>(
      ::osirixgrpc::_Status_default_instance_);
}
inline const ::osirixgrpc::Status& BrowserControllerDatabaseSelectionResponse::status() const {
  // @@protoc_insertion_point(field_get:osirixgrpc.BrowserControllerDatabaseSelectionResponse.status)
  return _internal_status();
}
inline void BrowserControllerDatabaseSelectionResponse::unsafe_arena_set_allocated_status(
    ::osirixgrpc::Status* status) {
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(status_);
  }
  status_ = status;
  if (status) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:osirixgrpc.BrowserControllerDatabaseSelectionResponse.status)
}
inline ::osirixgrpc::Status* BrowserControllerDatabaseSelectionResponse::release_status() {
  
  ::osirixgrpc::Status* temp = status_;
  status_ = nullptr;
  if (GetArena() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
  return temp;
}
inline ::osirixgrpc::Status* BrowserControllerDatabaseSelectionResponse::unsafe_arena_release_status() {
  // @@protoc_insertion_point(field_release:osirixgrpc.BrowserControllerDatabaseSelectionResponse.status)
  
  ::osirixgrpc::Status* temp = status_;
  status_ = nullptr;
  return temp;
}
inline ::osirixgrpc::Status* BrowserControllerDatabaseSelectionResponse::_internal_mutable_status() {
  
  if (status_ == nullptr) {
    auto* p = CreateMaybeMessage<::osirixgrpc::Status>(GetArena());
    status_ = p;
  }
  return status_;
}
inline ::osirixgrpc::Status* BrowserControllerDatabaseSelectionResponse::mutable_status() {
  // @@protoc_insertion_point(field_mutable:osirixgrpc.BrowserControllerDatabaseSelectionResponse.status)
  return _internal_mutable_status();
}
inline void BrowserControllerDatabaseSelectionResponse::set_allocated_status(::osirixgrpc::Status* status) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(status_);
  }
  if (status) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(status)->GetArena();
    if (message_arena != submessage_arena) {
      status = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, status, submessage_arena);
    }
    
  } else {
    
  }
  status_ = status;
  // @@protoc_insertion_point(field_set_allocated:osirixgrpc.BrowserControllerDatabaseSelectionResponse.status)
}

// repeated .osirixgrpc.DicomSeries series = 2;
inline int BrowserControllerDatabaseSelectionResponse::_internal_series_size() const {
  return series_.size();
}
inline int BrowserControllerDatabaseSelectionResponse::series_size() const {
  return _internal_series_size();
}
inline ::osirixgrpc::DicomSeries* BrowserControllerDatabaseSelectionResponse::mutable_series(int index) {
  // @@protoc_insertion_point(field_mutable:osirixgrpc.BrowserControllerDatabaseSelectionResponse.series)
  return series_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::osirixgrpc::DicomSeries >*
BrowserControllerDatabaseSelectionResponse::mutable_series() {
  // @@protoc_insertion_point(field_mutable_list:osirixgrpc.BrowserControllerDatabaseSelectionResponse.series)
  return &series_;
}
inline const ::osirixgrpc::DicomSeries& BrowserControllerDatabaseSelectionResponse::_internal_series(int index) const {
  return series_.Get(index);
}
inline const ::osirixgrpc::DicomSeries& BrowserControllerDatabaseSelectionResponse::series(int index) const {
  // @@protoc_insertion_point(field_get:osirixgrpc.BrowserControllerDatabaseSelectionResponse.series)
  return _internal_series(index);
}
inline ::osirixgrpc::DicomSeries* BrowserControllerDatabaseSelectionResponse::_internal_add_series() {
  return series_.Add();
}
inline ::osirixgrpc::DicomSeries* BrowserControllerDatabaseSelectionResponse::add_series() {
  // @@protoc_insertion_point(field_add:osirixgrpc.BrowserControllerDatabaseSelectionResponse.series)
  return _internal_add_series();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::osirixgrpc::DicomSeries >&
BrowserControllerDatabaseSelectionResponse::series() const {
  // @@protoc_insertion_point(field_list:osirixgrpc.BrowserControllerDatabaseSelectionResponse.series)
  return series_;
}

// repeated .osirixgrpc.DicomStudy studies = 3;
inline int BrowserControllerDatabaseSelectionResponse::_internal_studies_size() const {
  return studies_.size();
}
inline int BrowserControllerDatabaseSelectionResponse::studies_size() const {
  return _internal_studies_size();
}
inline ::osirixgrpc::DicomStudy* BrowserControllerDatabaseSelectionResponse::mutable_studies(int index) {
  // @@protoc_insertion_point(field_mutable:osirixgrpc.BrowserControllerDatabaseSelectionResponse.studies)
  return studies_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::osirixgrpc::DicomStudy >*
BrowserControllerDatabaseSelectionResponse::mutable_studies() {
  // @@protoc_insertion_point(field_mutable_list:osirixgrpc.BrowserControllerDatabaseSelectionResponse.studies)
  return &studies_;
}
inline const ::osirixgrpc::DicomStudy& BrowserControllerDatabaseSelectionResponse::_internal_studies(int index) const {
  return studies_.Get(index);
}
inline const ::osirixgrpc::DicomStudy& BrowserControllerDatabaseSelectionResponse::studies(int index) const {
  // @@protoc_insertion_point(field_get:osirixgrpc.BrowserControllerDatabaseSelectionResponse.studies)
  return _internal_studies(index);
}
inline ::osirixgrpc::DicomStudy* BrowserControllerDatabaseSelectionResponse::_internal_add_studies() {
  return studies_.Add();
}
inline ::osirixgrpc::DicomStudy* BrowserControllerDatabaseSelectionResponse::add_studies() {
  // @@protoc_insertion_point(field_add:osirixgrpc.BrowserControllerDatabaseSelectionResponse.studies)
  return _internal_add_studies();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::osirixgrpc::DicomStudy >&
BrowserControllerDatabaseSelectionResponse::studies() const {
  // @@protoc_insertion_point(field_list:osirixgrpc.BrowserControllerDatabaseSelectionResponse.studies)
  return studies_;
}

// -------------------------------------------------------------------

// BrowserControllerCopyFilesIfNeededRequest

// .osirixgrpc.BrowserController browser = 1;
inline bool BrowserControllerCopyFilesIfNeededRequest::_internal_has_browser() const {
  return this != internal_default_instance() && browser_ != nullptr;
}
inline bool BrowserControllerCopyFilesIfNeededRequest::has_browser() const {
  return _internal_has_browser();
}
inline const ::osirixgrpc::BrowserController& BrowserControllerCopyFilesIfNeededRequest::_internal_browser() const {
  const ::osirixgrpc::BrowserController* p = browser_;
  return p != nullptr ? *p : reinterpret_cast<const ::osirixgrpc::BrowserController&>(
      ::osirixgrpc::_BrowserController_default_instance_);
}
inline const ::osirixgrpc::BrowserController& BrowserControllerCopyFilesIfNeededRequest::browser() const {
  // @@protoc_insertion_point(field_get:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.browser)
  return _internal_browser();
}
inline void BrowserControllerCopyFilesIfNeededRequest::unsafe_arena_set_allocated_browser(
    ::osirixgrpc::BrowserController* browser) {
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(browser_);
  }
  browser_ = browser;
  if (browser) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.browser)
}
inline ::osirixgrpc::BrowserController* BrowserControllerCopyFilesIfNeededRequest::release_browser() {
  
  ::osirixgrpc::BrowserController* temp = browser_;
  browser_ = nullptr;
  if (GetArena() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
  return temp;
}
inline ::osirixgrpc::BrowserController* BrowserControllerCopyFilesIfNeededRequest::unsafe_arena_release_browser() {
  // @@protoc_insertion_point(field_release:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.browser)
  
  ::osirixgrpc::BrowserController* temp = browser_;
  browser_ = nullptr;
  return temp;
}
inline ::osirixgrpc::BrowserController* BrowserControllerCopyFilesIfNeededRequest::_internal_mutable_browser() {
  
  if (browser_ == nullptr) {
    auto* p = CreateMaybeMessage<::osirixgrpc::BrowserController>(GetArena());
    browser_ = p;
  }
  return browser_;
}
inline ::osirixgrpc::BrowserController* BrowserControllerCopyFilesIfNeededRequest::mutable_browser() {
  // @@protoc_insertion_point(field_mutable:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.browser)
  return _internal_mutable_browser();
}
inline void BrowserControllerCopyFilesIfNeededRequest::set_allocated_browser(::osirixgrpc::BrowserController* browser) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(browser_);
  }
  if (browser) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(browser)->GetArena();
    if (message_arena != submessage_arena) {
      browser = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, browser, submessage_arena);
    }
    
  } else {
    
  }
  browser_ = browser;
  // @@protoc_insertion_point(field_set_allocated:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.browser)
}

// repeated string paths = 2;
inline int BrowserControllerCopyFilesIfNeededRequest::_internal_paths_size() const {
  return paths_.size();
}
inline int BrowserControllerCopyFilesIfNeededRequest::paths_size() const {
  return _internal_paths_size();
}
inline void BrowserControllerCopyFilesIfNeededRequest::clear_paths() {
  paths_.Clear();
}
inline std::string* BrowserControllerCopyFilesIfNeededRequest::add_paths() {
  // @@protoc_insertion_point(field_add_mutable:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths)
  return _internal_add_paths();
}
inline const std::string& BrowserControllerCopyFilesIfNeededRequest::_internal_paths(int index) const {
  return paths_.Get(index);
}
inline const std::string& BrowserControllerCopyFilesIfNeededRequest::paths(int index) const {
  // @@protoc_insertion_point(field_get:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths)
  return _internal_paths(index);
}
inline std::string* BrowserControllerCopyFilesIfNeededRequest::mutable_paths(int index) {
  // @@protoc_insertion_point(field_mutable:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths)
  return paths_.Mutable(index);
}
inline void BrowserControllerCopyFilesIfNeededRequest::set_paths(int index, const std::string& value) {
  // @@protoc_insertion_point(field_set:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths)
  paths_.Mutable(index)->assign(value);
}
inline void BrowserControllerCopyFilesIfNeededRequest::set_paths(int index, std::string&& value) {
  // @@protoc_insertion_point(field_set:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths)
  paths_.Mutable(index)->assign(std::move(value));
}
inline void BrowserControllerCopyFilesIfNeededRequest::set_paths(int index, const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  paths_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths)
}
inline void BrowserControllerCopyFilesIfNeededRequest::set_paths(int index, const char* value, size_t size) {
  paths_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths)
}
inline std::string* BrowserControllerCopyFilesIfNeededRequest::_internal_add_paths() {
  return paths_.Add();
}
inline void BrowserControllerCopyFilesIfNeededRequest::add_paths(const std::string& value) {
  paths_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths)
}
inline void BrowserControllerCopyFilesIfNeededRequest::add_paths(std::string&& value) {
  paths_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths)
}
inline void BrowserControllerCopyFilesIfNeededRequest::add_paths(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  paths_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths)
}
inline void BrowserControllerCopyFilesIfNeededRequest::add_paths(const char* value, size_t size) {
  paths_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>&
BrowserControllerCopyFilesIfNeededRequest::paths() const {
  // @@protoc_insertion_point(field_list:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths)
  return paths_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>*
BrowserControllerCopyFilesIfNeededRequest::mutable_paths() {
  // @@protoc_insertion_point(field_mutable_list:osirixgrpc.BrowserControllerCopyFilesIfNeededRequest.paths)
  return &paths_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace osirixgrpc

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_browsercontroller_2eproto
