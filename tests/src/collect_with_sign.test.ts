import { processTest, populateTransaction } from "./test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "poly_hub_collect_with_sign"; // <= Name of the test
const testDirSuffix = "hub_collect_with_sign"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xc1e77ee73403b8a7478884915aa599932a677870"; // <= Address of the smart contract
const chainID = 1;

// From : https://polygonscan.com/tx/0x62d86ea86e2b88634584d371cf86ff4d61d3c7d49f4d6e8f6a5d5bc760afbd62
const inputData =
  "0xb7902e7300000000000000000000000000000000000000000000000000000000000000c0000000000000000000000000b794f5ea0ba39494ce839613fffba74279579268000000000000000000000000000000000000000000000000000000000000001b929dff750909eeef92081c57467f7fd6c040a42b9afbbc80a19179a9ffeb35bd929dff750909eeef92081c57467f7fd6c040a42b9afbbc80a19179a9ffeb35bd00000000000000000000000000000000000000000000000000000000000000030000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000030000000000000000000000000000000000000000000000000000000000000004000000000000000000000000000000000000000000000000000000000000000500000000000000000000000000000000000000000000000000000000000000c000000000000000000000000000000000000000000000000000000000000000042132312300000000000000000000000000000000000000000000000000000000";
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
