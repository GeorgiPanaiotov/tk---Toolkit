{-# LANGUAGE ForeignFunctionInterface #-}
{-# LANGUAGE LambdaCase #-}

module ELFF where

import Text.Printf
import Foreign.C.Types
import Foreign.Ptr
import Data.Word
import qualified Data.ByteString as BS
import qualified Data.ByteString.Unsafe as BSU

decodeType :: Word8 -> String
decodeType = \case
  0x00 -> "None"
  0x01 -> "REL Relocatable File"
  0x02 -> "EXEC Executable File"
  0x03 -> "DYN Shared Object"
  0x04 -> "CORE Core File"
  _    -> "Unknown"

decodeOSABI :: Word8 -> String
decodeOSABI = \case
  0x00 -> "UNIX - System V"
  0x01 -> "HP-UX"
  0x02 -> "NetBSD"
  0x03 -> "Linux"
  0x04 -> "GNU Hurd"
  0x06 -> "Solaris"
  0x07 -> "Advanced Interactive eXecutive"
  0x08 -> "IRIX"
  0x09 -> "Free BSD"
  0x0A -> "Tru64"
  0x0B -> "Novell Modesto"
  0x0C -> "Open BSD"
  0x0D -> "Open VMS"
  0x0E -> "NonStop Kernel"
  0x0F -> "AROS"
  0x10 -> "Fenix OS"
  0x11 -> "NUXI"
  0x12 -> "Open VOS"
  0xFF -> "Standalone / Embedded"
  val  -> "Unknown ABI (0x" ++ showHex val "" ++ ")"
  where showHex w = show

printC :: String -> String -> IO ()
printC field value = do
  printf "%-30s %s\n" field value

get_elf_bytes :: Ptr Word8 -> CSize -> Int -> IO Word8
get_elf_bytes ptr len byte = do
  bytes <- BSU.unsafePackCStringLen (castPtr ptr, fromIntegral len)
  if BS.length bytes < 8
    then error "This does not look like an ELF Header"
  else do
    let osabiByte = BS.index bytes byte
    return osabiByte

foreign export ccall hs_fmt_osabi :: Ptr Word8 -> CSize -> IO ()
hs_fmt_osabi :: Ptr Word8 -> CSize -> IO ()
hs_fmt_osabi ptr len = do
    osabiByte <- get_elf_bytes ptr len 0x07
    printC "OSABI: " (decodeOSABI osabiByte)

foreign export ccall hs_fmt_type :: Ptr Word8 -> CSize -> IO ()
hs_fmt_type :: Ptr Word8 -> CSize -> IO ()
hs_fmt_type ptr len = do
    typeByte <- get_elf_bytes ptr len 0x10
    printC "TYPE: " (decodeType typeByte)

main :: IO ()
main = undefined