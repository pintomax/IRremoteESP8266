// Copyright 2017 David Conran

#include "IRsend.h"
#include "IRsend_test.h"
#include "gtest/gtest.h"

// Tests for sendAiwaRCT501().

// Test sending typical data only.
TEST(TestSendAiwa, SendDataOnly) {
  IRsendTest irsend(4);
  irsend.begin();

  irsend.reset();
  irsend.sendAiwaRCT501(0x7F);  // Aiwa Power Toggle.
  EXPECT_EQ(
      "m9000s4500"
      "m560s560m560s1690m560s1690m560s1690m560s560m560s1690m560s1690m560s560"
      "m560s560m560s560m560s560m560s560m560s560m560s1690m560s560m560s560"
      "m560s560m560s1690m560s560m560s560m560s1690m560s1690m560s1690m560s1690"
      "m560s1690m560s1690m560s560m560s560m560s560m560s560m560s560m560s560"
      "m560s560m560s560m560s1690m560s1690m560s1690m560s1690m560s1690m560s1690"
      "m560s1690m560s1690m560s108000"
      "m9000s2250m560s108000", irsend.outputStr());
}

// Test sending oversized data.
TEST(TestSendAiwa, SendOversizedData) {
  IRsendTest irsend(4);
  irsend.begin();

  irsend.reset();
  irsend.sendAiwaRCT501(0x7F, 38);  // 38 bits is over the maximum. Should fail.
  EXPECT_EQ("", irsend.outputStr());
}

// Test sending with different repeats.
TEST(TestSendAiwa, SendWithRepeats) {
  IRsendTest irsend(4);
  irsend.begin();

  irsend.reset();
  irsend.sendAiwaRCT501(0x7F, AIWA_RC_T501_BITS, 0);  // No repeats.
  EXPECT_EQ(
      "m9000s4500"
      "m560s560m560s1690m560s1690m560s1690m560s560m560s1690m560s1690m560s560"
      "m560s560m560s560m560s560m560s560m560s560m560s1690m560s560m560s560"
      "m560s560m560s1690m560s560m560s560m560s1690m560s1690m560s1690m560s1690"
      "m560s1690m560s1690m560s560m560s560m560s560m560s560m560s560m560s560"
      "m560s560m560s560m560s1690m560s1690m560s1690m560s1690m560s1690m560s1690"
      "m560s1690m560s1690m560s108000", irsend.outputStr());
  irsend.reset();
  irsend.sendAiwaRCT501(0x7F, AIWA_RC_T501_BITS, 1);  // 1 repeat.
  EXPECT_EQ(
      "m9000s4500"
      "m560s560m560s1690m560s1690m560s1690m560s560m560s1690m560s1690m560s560"
      "m560s560m560s560m560s560m560s560m560s560m560s1690m560s560m560s560"
      "m560s560m560s1690m560s560m560s560m560s1690m560s1690m560s1690m560s1690"
      "m560s1690m560s1690m560s560m560s560m560s560m560s560m560s560m560s560"
      "m560s560m560s560m560s1690m560s1690m560s1690m560s1690m560s1690m560s1690"
      "m560s1690m560s1690m560s108000"
      "m9000s2250m560s108000", irsend.outputStr());
  irsend.reset();
  irsend.sendAiwaRCT501(0x7F, AIWA_RC_T501_BITS, 2);  // 2 repeats.
  EXPECT_EQ(
      "m9000s4500"
      "m560s560m560s1690m560s1690m560s1690m560s560m560s1690m560s1690m560s560"
      "m560s560m560s560m560s560m560s560m560s560m560s1690m560s560m560s560"
      "m560s560m560s1690m560s560m560s560m560s1690m560s1690m560s1690m560s1690"
      "m560s1690m560s1690m560s560m560s560m560s560m560s560m560s560m560s560"
      "m560s560m560s560m560s1690m560s1690m560s1690m560s1690m560s1690m560s1690"
      "m560s1690m560s1690m560s108000"
      "m9000s2250m560s108000"
      "m9000s2250m560s108000", irsend.outputStr());
}

// Test sending an atypical data size.
TEST(TestSendAiwa, SendUsualSize) {
  IRsendTest irsend(4);
  irsend.begin();

  irsend.reset();
  irsend.sendAiwaRCT501(0x12, 8);
  EXPECT_EQ(
      "m9000s4500"
      "m560s560m560s1690m560s1690m560s1690m560s560m560s1690m560s1690m560s560"
      "m560s560m560s560m560s560m560s560m560s560m560s1690m560s560m560s560"
      "m560s560m560s1690m560s560m560s560m560s1690m560s1690m560s1690m560s1690"
      "m560s1690m560s1690m560s560m560s560m560s560m560s1690m560s560m560s560"
      "m560s1690m560s560m560s1690m560s108000"
      "m9000s2250m560s108000", irsend.outputStr());

  irsend.reset();
  irsend.sendAiwaRCT501(0x1234567890, 37);
  EXPECT_EQ(
      "m9000s4500"
      "m560s560m560s1690m560s1690m560s1690m560s560m560s1690m560s1690m560s560"
      "m560s560m560s560m560s560m560s560m560s560m560s1690m560s560m560s560"
      "m560s560m560s1690m560s560m560s560m560s1690m560s1690m560s1690m560s1690"
      "m560s1690m560s1690m560s1690m560s560m560s560m560s1690m560s560m560s560"
      "m560s560m560s1690m560s1690m560s560m560s1690m560s560m560s560m560s560"
      "m560s1690m560s560m560s1690m560s560m560s1690m560s1690m560s560m560s560"
      "m560s1690m560s1690m560s1690m560s1690m560s560m560s560m560s560m560s1690"
      "m560s560m560s560m560s1690m560s560m560s560m560s560m560s560m560s1690"
      "m560s108000"
      "m9000s2250m560s108000", irsend.outputStr());
}

// Tests for decodeAiwaRCT501().

// Decode normal Aiwa messages.
TEST(TestDecodeAiwa, NormalDecodeWithStrict) {
  IRsendTest irsend(4);
  IRrecv irrecv(4);
  irsend.begin();

  // Normal Aiwa 16-bit message.
  irsend.reset();
  irsend.sendAiwaRCT501(0x7F);
  irsend.makeDecodeResult();
  ASSERT_TRUE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                      true));
  EXPECT_EQ(AIWA_RC_T501, irsend.capture.decode_type);
  EXPECT_EQ(AIWA_RC_T501_BITS, irsend.capture.bits);
  EXPECT_EQ(0x7F, irsend.capture.value);
  EXPECT_EQ(0x0, irsend.capture.address);
  EXPECT_EQ(0x0, irsend.capture.command);
  EXPECT_FALSE(irsend.capture.repeat);

  // Normal Aiwa 15-bit(42bit) message.
  irsend.reset();
  irsend.sendAiwaRCT501(0x0);
  irsend.makeDecodeResult();
  ASSERT_TRUE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                      true));
  EXPECT_EQ(AIWA_RC_T501, irsend.capture.decode_type);
  EXPECT_EQ(AIWA_RC_T501_BITS, irsend.capture.bits);
  EXPECT_EQ(0x0, irsend.capture.value);
  EXPECT_EQ(0x0, irsend.capture.address);
  EXPECT_EQ(0x0, irsend.capture.command);
  EXPECT_FALSE(irsend.capture.repeat);

  // Normal Aiwa 15-bit(42bit) message.
  irsend.reset();
  irsend.sendAiwaRCT501(0x7FFF);
  irsend.makeDecodeResult();
  ASSERT_TRUE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                      true));
  EXPECT_EQ(AIWA_RC_T501, irsend.capture.decode_type);
  EXPECT_EQ(AIWA_RC_T501_BITS, irsend.capture.bits);
  EXPECT_EQ(0x7FFF, irsend.capture.value);
  EXPECT_EQ(0x0, irsend.capture.address);
  EXPECT_EQ(0x0, irsend.capture.command);
  EXPECT_FALSE(irsend.capture.repeat);
}

// Decode normal repeated Aiwa messages.
TEST(TestDecodeAiwa, NormalDecodeWithRepeatAndStrict) {
  IRsendTest irsend(4);
  IRrecv irrecv(4);
  irsend.begin();

  // Normal Aiwa 15-bit(42bit) message with 2 repeats.
  irsend.reset();
  irsend.sendAiwaRCT501(0x7F, AIWA_RC_T501_BITS, 2);
  irsend.makeDecodeResult();
  ASSERT_TRUE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                      true));
  EXPECT_EQ(AIWA_RC_T501, irsend.capture.decode_type);
  EXPECT_EQ(AIWA_RC_T501_BITS, irsend.capture.bits);
  EXPECT_EQ(0x7F, irsend.capture.value);
  EXPECT_EQ(0x0, irsend.capture.address);
  EXPECT_EQ(0x0, irsend.capture.command);
  EXPECT_FALSE(irsend.capture.repeat);
}

// Decode unsupported Aiwa messages.
TEST(TestDecodeAiwa, DecodeWithNonStrictValues) {
  IRsendTest irsend(4);
  IRrecv irrecv(4);
  irsend.begin();

  irsend.reset();
  // Confirm using sendNEC(data, 42, 1) can make a legal Aiwa message.
  irsend.sendNEC(0x1D8113F00FF, 42, AIWA_RC_T501_MIN_REPEAT);
  irsend.makeDecodeResult();
  // MUST pass with strict on.
  ASSERT_TRUE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                       true));
  ASSERT_EQ(0x7F, irsend.capture.value);

  irsend.reset();
  // Use sendNEC(data, 42) to make/send an illegal value Aiwa message.
  // Value is illegal due to bad pre & post data.
  irsend.sendNEC(0x1234567890A, 42, AIWA_RC_T501_MIN_REPEAT);
  irsend.makeDecodeResult();
  // Should fail with strict on.
  ASSERT_FALSE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                       true));
  // Should fail if strict off too.
  ASSERT_FALSE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                      false));

  irsend.reset();
  // Use sendNEC(data, 42) to make/send an illegal value Aiwa message.
  // Value is illegal due to bad post data only.
  irsend.sendNEC(0x1D8113F00FE, 42, AIWA_RC_T501_MIN_REPEAT);
  irsend.makeDecodeResult();
  // Should fail with strict on.
  ASSERT_FALSE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                       true));
  // Should fail if strict off too.
  ASSERT_FALSE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                      false));

  irsend.reset();
  // Use sendNEC(data, 42) to make/send an illegal value Aiwa message.
  // Value is illegal due to bad pre data only.
  irsend.sendNEC(0x0D8113F00FF, 42, AIWA_RC_T501_MIN_REPEAT);
  irsend.makeDecodeResult();
  // Should fail with strict on.
  ASSERT_FALSE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                       true));
  // Should fail if strict off too.
  ASSERT_FALSE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                      false));
}

// Decode unsupported Aiwa messages.
TEST(TestDecodeAiwa, DecodeWithNonStrictSizes) {
  IRsendTest irsend(4);
  IRrecv irrecv(4);
  irsend.begin();

  irsend.reset();
  irsend.sendAiwaRCT501(0x0, 8);  // Illegal size Aiwa 8-bit message.
  irsend.makeDecodeResult();
  // Should fail with strict on.
  ASSERT_FALSE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                       true));
  // Should pass if strict off.
  ASSERT_TRUE(irrecv.decodeAiwaRCT501(&irsend.capture, 8, false));
  EXPECT_EQ(AIWA_RC_T501, irsend.capture.decode_type);
  EXPECT_EQ(8, irsend.capture.bits);
  EXPECT_EQ(0x0, irsend.capture.value);

  irsend.reset();
  irsend.sendAiwaRCT501(0x12345678, 32);  // Illegal size Aiwa 32-bit message.
  irsend.makeDecodeResult();
  // Should fail with strict on.
  ASSERT_FALSE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                      true));
  // Should fail with strict when we ask for the wrong bit size.
  ASSERT_FALSE(irrecv.decodeAiwaRCT501(&irsend.capture, 32, true));

  // Should pass if strict off.
  ASSERT_TRUE(irrecv.decodeAiwaRCT501(&irsend.capture, 32, false));
  EXPECT_EQ(AIWA_RC_T501, irsend.capture.decode_type);
  EXPECT_EQ(32, irsend.capture.bits);
  EXPECT_EQ(0x12345678, irsend.capture.value);
}

// Decode (non-standard) 64-bit messages.
TEST(TestDecodeAiwa, Decode64BitMessages) {
  IRsendTest irsend(4);
  IRrecv irrecv(4);
  irsend.begin();

  irsend.reset();
  // Illegal value & size Aiwa 37(64)-bit message.
  irsend.sendAiwaRCT501(0x1FFFFFFFFF, 37);
  irsend.makeDecodeResult();
  // Should work with a 'normal' match (not strict)
  ASSERT_TRUE(irrecv.decodeAiwaRCT501(&irsend.capture, 37, false));
  EXPECT_EQ(AIWA_RC_T501, irsend.capture.decode_type);
  EXPECT_EQ(37, irsend.capture.bits);
  EXPECT_EQ(0x1FFFFFFFFF, irsend.capture.value);

  // Reconfirm it by sending a true 64bit NEC message with the Aiwa prefix.
  irsend.reset();
  irsend.sendNEC(0x76044FFFFFFFFFFF, 64, AIWA_RC_T501_MIN_REPEAT);
  irsend.makeDecodeResult();
  // Should work with a 'normal' match (not strict)
  ASSERT_TRUE(irrecv.decodeAiwaRCT501(&irsend.capture, 37, false));
  EXPECT_EQ(AIWA_RC_T501, irsend.capture.decode_type);
  EXPECT_EQ(37, irsend.capture.bits);
  EXPECT_EQ(0x1FFFFFFFFF, irsend.capture.value);
}

// Decode a 'real' example via GlobalCache
TEST(TestDecodeAiwa, DecodeGlobalCacheExample) {
  IRsendTest irsend(4);
  IRrecv irrecv(4);
  irsend.begin();

  irsend.reset();
  // Aiwa Power Toggle from Global Cache.
  uint16_t gc_test[95] = {38000, 1, 89, 342, 171, 21, 21, 21, 64, 21, 64,
                          21, 64, 21, 21, 21, 64, 21, 64, 21, 21, 21, 21,
                          21, 21, 21, 21, 21, 21, 21, 21, 21, 64, 21, 21,
                          21, 21, 21, 21, 21, 64, 21, 21, 21, 21, 21, 64,
                          21, 64, 21, 64, 21, 64, 21, 64, 21, 64, 21, 21,
                          21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
                          21, 21, 21, 64, 21, 64, 21, 64, 21, 64, 21, 64,
                          21, 64, 21, 64, 21, 64, 21, 875, 342, 171, 21, 3565};
  irsend.sendGC(gc_test, 95);
  irsend.makeDecodeResult();

  ASSERT_TRUE(irrecv.decodeAiwaRCT501(&irsend.capture));
  EXPECT_EQ(AIWA_RC_T501, irsend.capture.decode_type);
  EXPECT_EQ(AIWA_RC_T501_BITS, irsend.capture.bits);
  EXPECT_EQ(0x7F, irsend.capture.value);
  EXPECT_EQ(0x0, irsend.capture.address);
  EXPECT_EQ(0x0, irsend.capture.command);
  EXPECT_FALSE(irsend.capture.repeat);

  // Confirm what the 42-bit NEC decode is.
  ASSERT_TRUE(irrecv.decodeNEC(&irsend.capture, 42, false));
  EXPECT_EQ(0x1D8113F00FF, irsend.capture.value);
}

// Fail to decode a non-Aiwa example via GlobalCache
TEST(TestDecodeAiwa, FailToDecodeNonAiwaExample) {
  IRsendTest irsend(4);
  IRrecv irrecv(4);
  irsend.begin();

  irsend.reset();
  uint16_t gc_test[39] = {38000, 1, 1, 322, 162, 20, 61, 20, 61, 20, 20, 20, 20,
                          20, 20, 20, 127, 20, 61, 9, 20, 20, 61, 20, 20, 20,
                          61, 20, 61, 20, 61, 20, 20, 20, 20, 20, 20, 20, 884};
  irsend.sendGC(gc_test, 39);
  irsend.makeDecodeResult();

  ASSERT_FALSE(irrecv.decodeAiwaRCT501(&irsend.capture));
  ASSERT_FALSE(irrecv.decodeAiwaRCT501(&irsend.capture, AIWA_RC_T501_BITS,
                                       false));
}