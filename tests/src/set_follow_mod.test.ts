import { processTest, populateTransaction } from "./test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "poly_hub_set_follow_mod"; // <= Name of the test
const testDirSuffix = "set_follow_mod"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xc1e77ee73403b8a7478884915aa599932a677870"; // <= Address of the smart contract
const chainID = 1;

// From : https://mumbai.polygonscan.com/tx/0x9283fb0bc353c5e4115d4571431a379e83ac8a5c66ca06a96d52b90443a87e51
const inputData =
  "0x6dea40b3000000000000000000000000000000000000000000000000000000000000000100000000000000000000000077f8d9af54b1c9d3e2ef117effd062025f5a2806000000000000000000000000000000000000000000000000000000000000006000000000000000000000000000000000000000000000000000000000000000600000000000000000000000002058a9d7613eee744279e3856ef0eada5fcbaa7e00000000000000000000000000000000000000000000000000000000041cdb40000000000000000000000000cb6c7b2e340d50701d45d55507f19a5ce5d72330";
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
