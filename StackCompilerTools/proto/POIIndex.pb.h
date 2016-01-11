// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: POIIndex.proto

#ifndef PROTOBUF_POIIndex_2eproto__INCLUDED
#define PROTOBUF_POIIndex_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006002 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace SK {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_POIIndex_2eproto();
void protobuf_AssignDesc_POIIndex_2eproto();
void protobuf_ShutdownFile_POIIndex_2eproto();

class POIIndex;
class POIIndex_mapPOI;
class POIIndex_mapPOI_stakePOI;
class POIIndex_mapPOI_stakePOI_typePOI;
class POIIndex_mapPOI_stakePOI_typePOI_POI;

// ===================================================================

class POIIndex_mapPOI_stakePOI_typePOI_POI : public ::google::protobuf::Message {
 public:
  POIIndex_mapPOI_stakePOI_typePOI_POI();
  virtual ~POIIndex_mapPOI_stakePOI_typePOI_POI();

  POIIndex_mapPOI_stakePOI_typePOI_POI(const POIIndex_mapPOI_stakePOI_typePOI_POI& from);

  inline POIIndex_mapPOI_stakePOI_typePOI_POI& operator=(const POIIndex_mapPOI_stakePOI_typePOI_POI& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const POIIndex_mapPOI_stakePOI_typePOI_POI& default_instance();

  void Swap(POIIndex_mapPOI_stakePOI_typePOI_POI* other);

  // implements Message ----------------------------------------------

  POIIndex_mapPOI_stakePOI_typePOI_POI* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const POIIndex_mapPOI_stakePOI_typePOI_POI& from);
  void MergeFrom(const POIIndex_mapPOI_stakePOI_typePOI_POI& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // required double Lat = 2;
  inline bool has_lat() const;
  inline void clear_lat();
  static const int kLatFieldNumber = 2;
  inline double lat() const;
  inline void set_lat(double value);

  // required double Lon = 3;
  inline bool has_lon() const;
  inline void clear_lon();
  static const int kLonFieldNumber = 3;
  inline double lon() const;
  inline void set_lon(double value);

  // @@protoc_insertion_point(class_scope:SK.POIIndex.mapPOI.stakePOI.typePOI.POI)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_lat();
  inline void clear_has_lat();
  inline void set_has_lon();
  inline void clear_has_lon();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* name_;
  double lat_;
  double lon_;
  friend void  protobuf_AddDesc_POIIndex_2eproto();
  friend void protobuf_AssignDesc_POIIndex_2eproto();
  friend void protobuf_ShutdownFile_POIIndex_2eproto();

  void InitAsDefaultInstance();
  static POIIndex_mapPOI_stakePOI_typePOI_POI* default_instance_;
};
// -------------------------------------------------------------------

class POIIndex_mapPOI_stakePOI_typePOI : public ::google::protobuf::Message {
 public:
  POIIndex_mapPOI_stakePOI_typePOI();
  virtual ~POIIndex_mapPOI_stakePOI_typePOI();

  POIIndex_mapPOI_stakePOI_typePOI(const POIIndex_mapPOI_stakePOI_typePOI& from);

  inline POIIndex_mapPOI_stakePOI_typePOI& operator=(const POIIndex_mapPOI_stakePOI_typePOI& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const POIIndex_mapPOI_stakePOI_typePOI& default_instance();

  void Swap(POIIndex_mapPOI_stakePOI_typePOI* other);

  // implements Message ----------------------------------------------

  POIIndex_mapPOI_stakePOI_typePOI* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const POIIndex_mapPOI_stakePOI_typePOI& from);
  void MergeFrom(const POIIndex_mapPOI_stakePOI_typePOI& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef POIIndex_mapPOI_stakePOI_typePOI_POI POI;

  // accessors -------------------------------------------------------

  // required int32 type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::google::protobuf::int32 type() const;
  inline void set_type(::google::protobuf::int32 value);

  // required .SK.POIIndex.mapPOI.stakePOI.typePOI.POI pois = 2;
  inline bool has_pois() const;
  inline void clear_pois();
  static const int kPoisFieldNumber = 2;
  inline const ::SK::POIIndex_mapPOI_stakePOI_typePOI_POI& pois() const;
  inline ::SK::POIIndex_mapPOI_stakePOI_typePOI_POI* mutable_pois();
  inline ::SK::POIIndex_mapPOI_stakePOI_typePOI_POI* release_pois();
  inline void set_allocated_pois(::SK::POIIndex_mapPOI_stakePOI_typePOI_POI* pois);

  // @@protoc_insertion_point(class_scope:SK.POIIndex.mapPOI.stakePOI.typePOI)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_pois();
  inline void clear_has_pois();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::SK::POIIndex_mapPOI_stakePOI_typePOI_POI* pois_;
  ::google::protobuf::int32 type_;
  friend void  protobuf_AddDesc_POIIndex_2eproto();
  friend void protobuf_AssignDesc_POIIndex_2eproto();
  friend void protobuf_ShutdownFile_POIIndex_2eproto();

  void InitAsDefaultInstance();
  static POIIndex_mapPOI_stakePOI_typePOI* default_instance_;
};
// -------------------------------------------------------------------

class POIIndex_mapPOI_stakePOI : public ::google::protobuf::Message {
 public:
  POIIndex_mapPOI_stakePOI();
  virtual ~POIIndex_mapPOI_stakePOI();

  POIIndex_mapPOI_stakePOI(const POIIndex_mapPOI_stakePOI& from);

  inline POIIndex_mapPOI_stakePOI& operator=(const POIIndex_mapPOI_stakePOI& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const POIIndex_mapPOI_stakePOI& default_instance();

  void Swap(POIIndex_mapPOI_stakePOI* other);

  // implements Message ----------------------------------------------

  POIIndex_mapPOI_stakePOI* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const POIIndex_mapPOI_stakePOI& from);
  void MergeFrom(const POIIndex_mapPOI_stakePOI& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef POIIndex_mapPOI_stakePOI_typePOI typePOI;

  // accessors -------------------------------------------------------

  // required int32 stakenum = 1;
  inline bool has_stakenum() const;
  inline void clear_stakenum();
  static const int kStakenumFieldNumber = 1;
  inline ::google::protobuf::int32 stakenum() const;
  inline void set_stakenum(::google::protobuf::int32 value);

  // required .SK.POIIndex.mapPOI.stakePOI.typePOI types = 2;
  inline bool has_types() const;
  inline void clear_types();
  static const int kTypesFieldNumber = 2;
  inline const ::SK::POIIndex_mapPOI_stakePOI_typePOI& types() const;
  inline ::SK::POIIndex_mapPOI_stakePOI_typePOI* mutable_types();
  inline ::SK::POIIndex_mapPOI_stakePOI_typePOI* release_types();
  inline void set_allocated_types(::SK::POIIndex_mapPOI_stakePOI_typePOI* types);

  // @@protoc_insertion_point(class_scope:SK.POIIndex.mapPOI.stakePOI)
 private:
  inline void set_has_stakenum();
  inline void clear_has_stakenum();
  inline void set_has_types();
  inline void clear_has_types();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::SK::POIIndex_mapPOI_stakePOI_typePOI* types_;
  ::google::protobuf::int32 stakenum_;
  friend void  protobuf_AddDesc_POIIndex_2eproto();
  friend void protobuf_AssignDesc_POIIndex_2eproto();
  friend void protobuf_ShutdownFile_POIIndex_2eproto();

  void InitAsDefaultInstance();
  static POIIndex_mapPOI_stakePOI* default_instance_;
};
// -------------------------------------------------------------------

class POIIndex_mapPOI : public ::google::protobuf::Message {
 public:
  POIIndex_mapPOI();
  virtual ~POIIndex_mapPOI();

  POIIndex_mapPOI(const POIIndex_mapPOI& from);

  inline POIIndex_mapPOI& operator=(const POIIndex_mapPOI& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const POIIndex_mapPOI& default_instance();

  void Swap(POIIndex_mapPOI* other);

  // implements Message ----------------------------------------------

  POIIndex_mapPOI* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const POIIndex_mapPOI& from);
  void MergeFrom(const POIIndex_mapPOI& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef POIIndex_mapPOI_stakePOI stakePOI;

  // accessors -------------------------------------------------------

  // required string code = 1;
  inline bool has_code() const;
  inline void clear_code();
  static const int kCodeFieldNumber = 1;
  inline const ::std::string& code() const;
  inline void set_code(const ::std::string& value);
  inline void set_code(const char* value);
  inline void set_code(const char* value, size_t size);
  inline ::std::string* mutable_code();
  inline ::std::string* release_code();
  inline void set_allocated_code(::std::string* code);

  // required int32 dir = 2;
  inline bool has_dir() const;
  inline void clear_dir();
  static const int kDirFieldNumber = 2;
  inline ::google::protobuf::int32 dir() const;
  inline void set_dir(::google::protobuf::int32 value);

  // repeated .SK.POIIndex.mapPOI.stakePOI stakepois = 3;
  inline int stakepois_size() const;
  inline void clear_stakepois();
  static const int kStakepoisFieldNumber = 3;
  inline const ::SK::POIIndex_mapPOI_stakePOI& stakepois(int index) const;
  inline ::SK::POIIndex_mapPOI_stakePOI* mutable_stakepois(int index);
  inline ::SK::POIIndex_mapPOI_stakePOI* add_stakepois();
  inline const ::google::protobuf::RepeatedPtrField< ::SK::POIIndex_mapPOI_stakePOI >&
      stakepois() const;
  inline ::google::protobuf::RepeatedPtrField< ::SK::POIIndex_mapPOI_stakePOI >*
      mutable_stakepois();

  // @@protoc_insertion_point(class_scope:SK.POIIndex.mapPOI)
 private:
  inline void set_has_code();
  inline void clear_has_code();
  inline void set_has_dir();
  inline void clear_has_dir();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* code_;
  ::google::protobuf::RepeatedPtrField< ::SK::POIIndex_mapPOI_stakePOI > stakepois_;
  ::google::protobuf::int32 dir_;
  friend void  protobuf_AddDesc_POIIndex_2eproto();
  friend void protobuf_AssignDesc_POIIndex_2eproto();
  friend void protobuf_ShutdownFile_POIIndex_2eproto();

  void InitAsDefaultInstance();
  static POIIndex_mapPOI* default_instance_;
};
// -------------------------------------------------------------------

class POIIndex : public ::google::protobuf::Message {
 public:
  POIIndex();
  virtual ~POIIndex();

  POIIndex(const POIIndex& from);

  inline POIIndex& operator=(const POIIndex& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const POIIndex& default_instance();

  void Swap(POIIndex* other);

  // implements Message ----------------------------------------------

  POIIndex* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const POIIndex& from);
  void MergeFrom(const POIIndex& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef POIIndex_mapPOI mapPOI;

  // accessors -------------------------------------------------------

  // required int32 iCount = 1;
  inline bool has_icount() const;
  inline void clear_icount();
  static const int kICountFieldNumber = 1;
  inline ::google::protobuf::int32 icount() const;
  inline void set_icount(::google::protobuf::int32 value);

  // repeated .SK.POIIndex.mapPOI roads = 2;
  inline int roads_size() const;
  inline void clear_roads();
  static const int kRoadsFieldNumber = 2;
  inline const ::SK::POIIndex_mapPOI& roads(int index) const;
  inline ::SK::POIIndex_mapPOI* mutable_roads(int index);
  inline ::SK::POIIndex_mapPOI* add_roads();
  inline const ::google::protobuf::RepeatedPtrField< ::SK::POIIndex_mapPOI >&
      roads() const;
  inline ::google::protobuf::RepeatedPtrField< ::SK::POIIndex_mapPOI >*
      mutable_roads();

  // @@protoc_insertion_point(class_scope:SK.POIIndex)
 private:
  inline void set_has_icount();
  inline void clear_has_icount();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::SK::POIIndex_mapPOI > roads_;
  ::google::protobuf::int32 icount_;
  friend void  protobuf_AddDesc_POIIndex_2eproto();
  friend void protobuf_AssignDesc_POIIndex_2eproto();
  friend void protobuf_ShutdownFile_POIIndex_2eproto();

  void InitAsDefaultInstance();
  static POIIndex* default_instance_;
};
// ===================================================================


// ===================================================================

// POIIndex_mapPOI_stakePOI_typePOI_POI

// required string name = 1;
inline bool POIIndex_mapPOI_stakePOI_typePOI_POI::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::clear_name() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& POIIndex_mapPOI_stakePOI_typePOI_POI::name() const {
  // @@protoc_insertion_point(field_get:SK.POIIndex.mapPOI.stakePOI.typePOI.POI.name)
  return *name_;
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set:SK.POIIndex.mapPOI.stakePOI.typePOI.POI.name)
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set_char:SK.POIIndex.mapPOI.stakePOI.typePOI.POI.name)
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:SK.POIIndex.mapPOI.stakePOI.typePOI.POI.name)
}
inline ::std::string* POIIndex_mapPOI_stakePOI_typePOI_POI::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:SK.POIIndex.mapPOI.stakePOI.typePOI.POI.name)
  return name_;
}
inline ::std::string* POIIndex_mapPOI_stakePOI_typePOI_POI::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:SK.POIIndex.mapPOI.stakePOI.typePOI.POI.name)
}

// required double Lat = 2;
inline bool POIIndex_mapPOI_stakePOI_typePOI_POI::has_lat() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::set_has_lat() {
  _has_bits_[0] |= 0x00000002u;
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::clear_has_lat() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::clear_lat() {
  lat_ = 0;
  clear_has_lat();
}
inline double POIIndex_mapPOI_stakePOI_typePOI_POI::lat() const {
  // @@protoc_insertion_point(field_get:SK.POIIndex.mapPOI.stakePOI.typePOI.POI.Lat)
  return lat_;
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::set_lat(double value) {
  set_has_lat();
  lat_ = value;
  // @@protoc_insertion_point(field_set:SK.POIIndex.mapPOI.stakePOI.typePOI.POI.Lat)
}

// required double Lon = 3;
inline bool POIIndex_mapPOI_stakePOI_typePOI_POI::has_lon() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::set_has_lon() {
  _has_bits_[0] |= 0x00000004u;
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::clear_has_lon() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::clear_lon() {
  lon_ = 0;
  clear_has_lon();
}
inline double POIIndex_mapPOI_stakePOI_typePOI_POI::lon() const {
  // @@protoc_insertion_point(field_get:SK.POIIndex.mapPOI.stakePOI.typePOI.POI.Lon)
  return lon_;
}
inline void POIIndex_mapPOI_stakePOI_typePOI_POI::set_lon(double value) {
  set_has_lon();
  lon_ = value;
  // @@protoc_insertion_point(field_set:SK.POIIndex.mapPOI.stakePOI.typePOI.POI.Lon)
}

// -------------------------------------------------------------------

// POIIndex_mapPOI_stakePOI_typePOI

// required int32 type = 1;
inline bool POIIndex_mapPOI_stakePOI_typePOI::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void POIIndex_mapPOI_stakePOI_typePOI::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void POIIndex_mapPOI_stakePOI_typePOI::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void POIIndex_mapPOI_stakePOI_typePOI::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::google::protobuf::int32 POIIndex_mapPOI_stakePOI_typePOI::type() const {
  // @@protoc_insertion_point(field_get:SK.POIIndex.mapPOI.stakePOI.typePOI.type)
  return type_;
}
inline void POIIndex_mapPOI_stakePOI_typePOI::set_type(::google::protobuf::int32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:SK.POIIndex.mapPOI.stakePOI.typePOI.type)
}

// required .SK.POIIndex.mapPOI.stakePOI.typePOI.POI pois = 2;
inline bool POIIndex_mapPOI_stakePOI_typePOI::has_pois() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void POIIndex_mapPOI_stakePOI_typePOI::set_has_pois() {
  _has_bits_[0] |= 0x00000002u;
}
inline void POIIndex_mapPOI_stakePOI_typePOI::clear_has_pois() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void POIIndex_mapPOI_stakePOI_typePOI::clear_pois() {
  if (pois_ != NULL) pois_->::SK::POIIndex_mapPOI_stakePOI_typePOI_POI::Clear();
  clear_has_pois();
}
inline const ::SK::POIIndex_mapPOI_stakePOI_typePOI_POI& POIIndex_mapPOI_stakePOI_typePOI::pois() const {
  // @@protoc_insertion_point(field_get:SK.POIIndex.mapPOI.stakePOI.typePOI.pois)
  return pois_ != NULL ? *pois_ : *default_instance_->pois_;
}
inline ::SK::POIIndex_mapPOI_stakePOI_typePOI_POI* POIIndex_mapPOI_stakePOI_typePOI::mutable_pois() {
  set_has_pois();
  if (pois_ == NULL) pois_ = new ::SK::POIIndex_mapPOI_stakePOI_typePOI_POI;
  // @@protoc_insertion_point(field_mutable:SK.POIIndex.mapPOI.stakePOI.typePOI.pois)
  return pois_;
}
inline ::SK::POIIndex_mapPOI_stakePOI_typePOI_POI* POIIndex_mapPOI_stakePOI_typePOI::release_pois() {
  clear_has_pois();
  ::SK::POIIndex_mapPOI_stakePOI_typePOI_POI* temp = pois_;
  pois_ = NULL;
  return temp;
}
inline void POIIndex_mapPOI_stakePOI_typePOI::set_allocated_pois(::SK::POIIndex_mapPOI_stakePOI_typePOI_POI* pois) {
  delete pois_;
  pois_ = pois;
  if (pois) {
    set_has_pois();
  } else {
    clear_has_pois();
  }
  // @@protoc_insertion_point(field_set_allocated:SK.POIIndex.mapPOI.stakePOI.typePOI.pois)
}

// -------------------------------------------------------------------

// POIIndex_mapPOI_stakePOI

// required int32 stakenum = 1;
inline bool POIIndex_mapPOI_stakePOI::has_stakenum() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void POIIndex_mapPOI_stakePOI::set_has_stakenum() {
  _has_bits_[0] |= 0x00000001u;
}
inline void POIIndex_mapPOI_stakePOI::clear_has_stakenum() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void POIIndex_mapPOI_stakePOI::clear_stakenum() {
  stakenum_ = 0;
  clear_has_stakenum();
}
inline ::google::protobuf::int32 POIIndex_mapPOI_stakePOI::stakenum() const {
  // @@protoc_insertion_point(field_get:SK.POIIndex.mapPOI.stakePOI.stakenum)
  return stakenum_;
}
inline void POIIndex_mapPOI_stakePOI::set_stakenum(::google::protobuf::int32 value) {
  set_has_stakenum();
  stakenum_ = value;
  // @@protoc_insertion_point(field_set:SK.POIIndex.mapPOI.stakePOI.stakenum)
}

// required .SK.POIIndex.mapPOI.stakePOI.typePOI types = 2;
inline bool POIIndex_mapPOI_stakePOI::has_types() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void POIIndex_mapPOI_stakePOI::set_has_types() {
  _has_bits_[0] |= 0x00000002u;
}
inline void POIIndex_mapPOI_stakePOI::clear_has_types() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void POIIndex_mapPOI_stakePOI::clear_types() {
  if (types_ != NULL) types_->::SK::POIIndex_mapPOI_stakePOI_typePOI::Clear();
  clear_has_types();
}
inline const ::SK::POIIndex_mapPOI_stakePOI_typePOI& POIIndex_mapPOI_stakePOI::types() const {
  // @@protoc_insertion_point(field_get:SK.POIIndex.mapPOI.stakePOI.types)
  return types_ != NULL ? *types_ : *default_instance_->types_;
}
inline ::SK::POIIndex_mapPOI_stakePOI_typePOI* POIIndex_mapPOI_stakePOI::mutable_types() {
  set_has_types();
  if (types_ == NULL) types_ = new ::SK::POIIndex_mapPOI_stakePOI_typePOI;
  // @@protoc_insertion_point(field_mutable:SK.POIIndex.mapPOI.stakePOI.types)
  return types_;
}
inline ::SK::POIIndex_mapPOI_stakePOI_typePOI* POIIndex_mapPOI_stakePOI::release_types() {
  clear_has_types();
  ::SK::POIIndex_mapPOI_stakePOI_typePOI* temp = types_;
  types_ = NULL;
  return temp;
}
inline void POIIndex_mapPOI_stakePOI::set_allocated_types(::SK::POIIndex_mapPOI_stakePOI_typePOI* types) {
  delete types_;
  types_ = types;
  if (types) {
    set_has_types();
  } else {
    clear_has_types();
  }
  // @@protoc_insertion_point(field_set_allocated:SK.POIIndex.mapPOI.stakePOI.types)
}

// -------------------------------------------------------------------

// POIIndex_mapPOI

// required string code = 1;
inline bool POIIndex_mapPOI::has_code() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void POIIndex_mapPOI::set_has_code() {
  _has_bits_[0] |= 0x00000001u;
}
inline void POIIndex_mapPOI::clear_has_code() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void POIIndex_mapPOI::clear_code() {
  if (code_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    code_->clear();
  }
  clear_has_code();
}
inline const ::std::string& POIIndex_mapPOI::code() const {
  // @@protoc_insertion_point(field_get:SK.POIIndex.mapPOI.code)
  return *code_;
}
inline void POIIndex_mapPOI::set_code(const ::std::string& value) {
  set_has_code();
  if (code_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    code_ = new ::std::string;
  }
  code_->assign(value);
  // @@protoc_insertion_point(field_set:SK.POIIndex.mapPOI.code)
}
inline void POIIndex_mapPOI::set_code(const char* value) {
  set_has_code();
  if (code_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    code_ = new ::std::string;
  }
  code_->assign(value);
  // @@protoc_insertion_point(field_set_char:SK.POIIndex.mapPOI.code)
}
inline void POIIndex_mapPOI::set_code(const char* value, size_t size) {
  set_has_code();
  if (code_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    code_ = new ::std::string;
  }
  code_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:SK.POIIndex.mapPOI.code)
}
inline ::std::string* POIIndex_mapPOI::mutable_code() {
  set_has_code();
  if (code_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    code_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:SK.POIIndex.mapPOI.code)
  return code_;
}
inline ::std::string* POIIndex_mapPOI::release_code() {
  clear_has_code();
  if (code_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = code_;
    code_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void POIIndex_mapPOI::set_allocated_code(::std::string* code) {
  if (code_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete code_;
  }
  if (code) {
    set_has_code();
    code_ = code;
  } else {
    clear_has_code();
    code_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:SK.POIIndex.mapPOI.code)
}

// required int32 dir = 2;
inline bool POIIndex_mapPOI::has_dir() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void POIIndex_mapPOI::set_has_dir() {
  _has_bits_[0] |= 0x00000002u;
}
inline void POIIndex_mapPOI::clear_has_dir() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void POIIndex_mapPOI::clear_dir() {
  dir_ = 0;
  clear_has_dir();
}
inline ::google::protobuf::int32 POIIndex_mapPOI::dir() const {
  // @@protoc_insertion_point(field_get:SK.POIIndex.mapPOI.dir)
  return dir_;
}
inline void POIIndex_mapPOI::set_dir(::google::protobuf::int32 value) {
  set_has_dir();
  dir_ = value;
  // @@protoc_insertion_point(field_set:SK.POIIndex.mapPOI.dir)
}

// repeated .SK.POIIndex.mapPOI.stakePOI stakepois = 3;
inline int POIIndex_mapPOI::stakepois_size() const {
  return stakepois_.size();
}
inline void POIIndex_mapPOI::clear_stakepois() {
  stakepois_.Clear();
}
inline const ::SK::POIIndex_mapPOI_stakePOI& POIIndex_mapPOI::stakepois(int index) const {
  // @@protoc_insertion_point(field_get:SK.POIIndex.mapPOI.stakepois)
  return stakepois_.Get(index);
}
inline ::SK::POIIndex_mapPOI_stakePOI* POIIndex_mapPOI::mutable_stakepois(int index) {
  // @@protoc_insertion_point(field_mutable:SK.POIIndex.mapPOI.stakepois)
  return stakepois_.Mutable(index);
}
inline ::SK::POIIndex_mapPOI_stakePOI* POIIndex_mapPOI::add_stakepois() {
  // @@protoc_insertion_point(field_add:SK.POIIndex.mapPOI.stakepois)
  return stakepois_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::SK::POIIndex_mapPOI_stakePOI >&
POIIndex_mapPOI::stakepois() const {
  // @@protoc_insertion_point(field_list:SK.POIIndex.mapPOI.stakepois)
  return stakepois_;
}
inline ::google::protobuf::RepeatedPtrField< ::SK::POIIndex_mapPOI_stakePOI >*
POIIndex_mapPOI::mutable_stakepois() {
  // @@protoc_insertion_point(field_mutable_list:SK.POIIndex.mapPOI.stakepois)
  return &stakepois_;
}

// -------------------------------------------------------------------

// POIIndex

// required int32 iCount = 1;
inline bool POIIndex::has_icount() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void POIIndex::set_has_icount() {
  _has_bits_[0] |= 0x00000001u;
}
inline void POIIndex::clear_has_icount() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void POIIndex::clear_icount() {
  icount_ = 0;
  clear_has_icount();
}
inline ::google::protobuf::int32 POIIndex::icount() const {
  // @@protoc_insertion_point(field_get:SK.POIIndex.iCount)
  return icount_;
}
inline void POIIndex::set_icount(::google::protobuf::int32 value) {
  set_has_icount();
  icount_ = value;
  // @@protoc_insertion_point(field_set:SK.POIIndex.iCount)
}

// repeated .SK.POIIndex.mapPOI roads = 2;
inline int POIIndex::roads_size() const {
  return roads_.size();
}
inline void POIIndex::clear_roads() {
  roads_.Clear();
}
inline const ::SK::POIIndex_mapPOI& POIIndex::roads(int index) const {
  // @@protoc_insertion_point(field_get:SK.POIIndex.roads)
  return roads_.Get(index);
}
inline ::SK::POIIndex_mapPOI* POIIndex::mutable_roads(int index) {
  // @@protoc_insertion_point(field_mutable:SK.POIIndex.roads)
  return roads_.Mutable(index);
}
inline ::SK::POIIndex_mapPOI* POIIndex::add_roads() {
  // @@protoc_insertion_point(field_add:SK.POIIndex.roads)
  return roads_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::SK::POIIndex_mapPOI >&
POIIndex::roads() const {
  // @@protoc_insertion_point(field_list:SK.POIIndex.roads)
  return roads_;
}
inline ::google::protobuf::RepeatedPtrField< ::SK::POIIndex_mapPOI >*
POIIndex::mutable_roads() {
  // @@protoc_insertion_point(field_mutable_list:SK.POIIndex.roads)
  return &roads_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace SK

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_POIIndex_2eproto__INCLUDED
