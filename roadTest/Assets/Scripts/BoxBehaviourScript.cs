using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoxBehaviourScript : MonoBehaviour {
    bool isColide = false;
    float RoadSpeed;
    // Use this for initialization
    void Start()
    {
        float r = Random.Range(50.0f, 100.0f);
        transform.position = new Vector3(0, 1, r);
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
            isColide = false;
            this.GetComponent<Collider>().isTrigger = true;
        }

        if (transform.position.y < 1)
        {
           
            transform.position = new Vector3(
                transform.position.x,
                1,
                transform.position.z);//GameObject.Find("Car").transform.position.z +
        }
        Vector3 move = new Vector3(0, 0, -1);
        transform.position += move * RoadSpeed * Time.deltaTime;
    }

    void OnTriggerEnter(Collider other)
    {
        if(other.name == "Car")
        {
            this.GetComponent<Collider>().isTrigger = false;
        }
        isColide = true;
    }

}
