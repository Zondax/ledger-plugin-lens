import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "polyhub_collect_with_sign"; // <= Name of the test
const testDirSuffix = "hub_collect_with_sign"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xdb46d1dc155634fbc732f92e853b10b288ad5a1d"; // <= Address of the smart contract
const chainID = 1;

// From : https://polygonscan.com/tx/0x62d86ea86e2b88634584d371cf86ff4d61d3c7d49f4d6e8f6a5d5bc760afbd62
const inputData =
  "0xb7902e7300000000000000000000000000000000000000000000000000000000000000c0000000000000000000000000b728dc8883dc872a58e20f1a0bd09e39ec8e51f5000000000000000000000000000000000000000000000000000000000000001bcdaeba6efe1d3489f3afa738c68e32bfe1d8674ceee02aaa4a8ca95cb549e20f71fe8730feb90dacfd57a6db293313ef12d180f164ef1aa7dfd4c5cde41773d800000000000000000000000000000000000000000000000000000000000000030000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000030000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000c00000000000000000000000000000000000000000000000000000000000000000";
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
    steps: 7, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanox",
    label: "Nano X",
    steps: 7, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanosp",
    label: "Nano S+",
    steps: 7, // <= Define the number of steps for this test case and this device
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
