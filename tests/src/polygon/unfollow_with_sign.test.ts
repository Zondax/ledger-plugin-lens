import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "polyhub_unfollow_with_sign"; // <= Name of the test
const testDirSuffix = "hub_unfollow_with_sign"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xdb46d1dc155634fbc732f92e853b10b288ad5a1d"; // <= Address of the smart contract
const chainID = 1;

// https://polygonscan.com/address/0xD4F2F33680FCCb36748FA9831851643781608844#writeProxyContract
const inputData =
  "0x809d8947000000000000000000000000000000000000000000000000000000000000000300000000000000000000000000000000000000000000000000000000000000e0000000000000000000000000b728dc8883dc872a58e20f1a0bd09e39ec8e51f5000000000000000000000000000000000000000000000000000000000000001ca6a1360cacbce86c7236bcca35d7781a78070d3895fac3224221fb3eb72c3eb33cfc75649a3363ac68d249d30d741521ea8a0138b557d15fedc7397bd85a087c0000000000000000000000000000000000000000000000000000000065061a3400000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000002";
// Create serializedTx and remove the "0x" prefix
const value = "3.1";
const serializedTx = populateTransaction(
  contractAddr,
  inputData,
  chainID,
  value
);
const devices = [
  {
    name: "nanos",
    label: "Nano S",
    steps: 5, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanox",
    label: "Nano X",
    steps: 5, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanosp",
    label: "Nano S+",
    steps: 5, // <= Define the number of steps for this test case and this device
  },
];

devices.forEach((device) =>
  processTest(
    device,
    contractName,
    testLabel,
    testDirSuffix,
    "",
    signedPlugin,
    serializedTx,
    testNetwork
  )
);
