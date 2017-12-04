using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GiftBehaviourScript : MonoBehaviour {

    
    float RoadSpeed;
    // Use this for initialization
    void Start()
    {
        transform.position = new Vector3(0.3f, 1, 70);
    }

    // Update is called once per frame
    void Update()
    {
        RoadSpeed = CarBehaviourScript.carSpeed;
        if (transform.position.z <= -60)
        {
            float r = Random.Range(-3.0f, 3.0f);
            transform.position = new Vector3(
                r,
                1,
                100);//GameObject.Find("Car").transform.position.z +
        }
        Vector3 move = new Vector3(0, 0, -1);
        transform.position += move * RoadSpeed * Time.deltaTime;
    }

    void OnTriggerEnter(Collider other)
    {
        transform.position = new Vector3(
                0,
                1,
                -60);//GameObject.Find("Car").transform.position.z +
    }

}
