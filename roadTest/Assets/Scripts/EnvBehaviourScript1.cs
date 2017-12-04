using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnvBehaviourScript1 : MonoBehaviour {

    public GameObject[] RoadPieces;

    const float RoadLength = 20f; //length of roads
    // Use this for initialization
    void Start()
    {
        RoadPieces = new GameObject[100];


        GameObject.Find("right").transform.localScale += (new Vector3(0.0f, 0.0f, 2000.0f));
        GameObject.Find("left").transform.localScale  += (new Vector3(0.0f, 0.0f, 2000.0f));
        //GameObject.Find("right").transform.position += (new Vector3(0.0f, 0.0f, 240.0f));
        //GameObject.Find("left").transform.position += (new Vector3(0.0f, 0.0f, 240.0f));

        for (int i = -200; i < 200; i+=10)
        {
            for (int j = -200; j < 200; j += 10)
            {
                GameObject G = Instantiate(GameObject.Find("Ground"));
                G.transform.position = new Vector3(
                    (float)i,
                    G.transform.position.y,
                    (float)j);
                
            }
        }


        float currentZ = 10f;
        for (int i = 0; i < RoadPieces.Length; i++)
        {
            RoadPieces[i] = Instantiate(GameObject.Find("Road"));
            RoadPieces[i].transform.position = new Vector3(
                RoadPieces[i].transform.position.x,
                RoadPieces[i].transform.position.y,
                currentZ + RoadLength);
            currentZ += RoadLength;
        }

    }

    // Update is called once per frame
    void Update () {

        if(GameObject.Find("Road").transform.position.z <= -(RoadLength * RoadLength / 2))
        {
            GameObject.Find("Road").transform.position = new Vector3(
                    GameObject.Find("Road").transform.position.x,
                    GameObject.Find("Road").transform.position.y,
                    5);
            float currentZ = 5f;

            for (int i = 0; i < RoadPieces.Length; i++)
            {
                //RoadPieces[i] = Instantiate(GameObject.Find("Road"));
                RoadPieces[i].transform.position = new Vector3(
                    RoadPieces[i].transform.position.x,
                    RoadPieces[i].transform.position.y,
                    currentZ + RoadLength);
                currentZ += RoadLength;
            }


        }
        
    }
}
