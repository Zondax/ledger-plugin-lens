import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "polyhub_metadata_with_sign"; // <= Name of the test
const testDirSuffix = "hub_metadata_with_sign"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xdb46d1dc155634fbc732f92e853b10b288ad5a1d"; // <= Address of the smart contract
const chainID = 1;

// https://polygonscan.com/address/0xDb46d1Dc155634FbC732f92E853b10B288AD5a1d#writeProxyContract
const inputData =
  "0x6d0fd658000000000000000000000000000000000000000000000000000000000000003400000000000000000000000000000000000000000000000000000000000000e0000000000000000000000000a8535b8049948be1bfeb1404daeabbd407792411000000000000000000000000000000000000000000000000000000000000001b900971919f923f9c4ec8afa8100fcde67b1506432e42dc7f170605de69c0b0c37d77635e1f1979bc7d35e772c8fe6ee988b60febb3b9d341e10ab17be36f9861000000000000000000000000000000000000000000000000000000006513f9fb000000000000000000000000000000000000000000000000000000000000003061723a2f2f7268754178766a644a46476c583133304d6c34386c3841494e582d59483066735372493265544f7945653800000000000000000000000000000000";
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
    steps: 6, // <= Define the number of steps for this test case and this device
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
