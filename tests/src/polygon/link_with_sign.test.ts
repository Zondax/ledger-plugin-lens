import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "polyhub_link_with_sign"; // <= Name of the test
const testDirSuffix = "hub_link_with_sign"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xd4f2f33680fccb36748fa9831851643781608844"; // <= Address of the smart contract
const chainID = 1;

// https://polygonscan.com/address/0xD4F2F33680FCCb36748FA9831851643781608844#writeProxyContract
const inputData =
  "0x7e502fe00000000000000000000000000000000000000000000000000000000000000159000000000000000000000000000000000000000000000000000000000000092600000000000000000000000055019eedab2acb5580bad02454b22adf5c37952a000000000000000000000000000000000000000000000000000000000000001be576e75396ad344da651c665b700bf95ea2acac05391214baff1733bfb92b1372c6032a0b192beef892871a14cad2294e95629087c86b4b186d3586ee7872bcb000000000000000000000000000000000000000000000000000000006506ffa5";
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
    steps: 6, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanosp",
    label: "Nano S+",
    steps: 6, // <= Define the number of steps for this test case and this device
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
