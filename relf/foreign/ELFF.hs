{-# LANGUAGE ForeignFunctionInterface #-}
{-# LANGUAGE LambdaCase #-}

module ELFF where

import Foreign.C.Types
import Foreign.Ptr
import Data.Word
import qualified Data.ByteString as BS
import qualified Data.ByteString.Unsafe as BSU

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
  val -> "Unknown ABI (0x" ++ showHex val "" ++ ")"
  where showHex w = show


foreign export ccall hs_fmt_osabi :: Ptr Word8 -> CSize -> IO ()
hs_fmt_osabi :: Ptr Word8 -> CSize -> IO ()
hs_fmt_osabi ptr len = do
  bytes <- BSU.unsafePackCStringLen (castPtr ptr, fromIntegral len)
  if BS.length bytes < 8
    then putStrLn "Error: This does not look like an ELF Header"
  else do
    let osabiByte = BS.index bytes 7
    putStrLn $ "OSABI: " ++ decodeOSABI osabiByte


main :: IO ()
main = undefined

-- ghc --make -dynamic -shared -fPIC Main.hs -o libhs.so
-- objdump -p lib.so
-- gcc main.c   -I/usr/lib/ghc/lib/x86_64-linux-ghc-9.4.7/rts-1.0.2/include   -L.   -L/usr/lib/ghc/lib/x86_64-linux-ghc-9.4.7   -Wl,-rpath,'$ORIGIN'   -Wl,-rpath,/usr/lib/ghc/lib/x86_64-linux-ghc-9.4.7   -l:libHSbase-4.17.2.0-ghc9.4.7.so   -l:libHSghc-bignum-1.3-ghc9.4.7.so   -l:libHSghc-prim-0.9.1-ghc9.4.7.so   -l:libHSrts-1.0.2-ghc9.4.7.so   -lgmp -lm   ./libhs.so -o ht