using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoadBehaviourScript : MonoBehaviour {

    float RoadSpeed;
    // Use this for initialization
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        RoadSpeed = CarBehaviourScript.carSpeed;

        if (Input.GetAxis("Vertical") > 0)
        {
            CarBehaviourScript.carSpeed += 0.01f;
        }
        else if (Input.GetAxis("Vertical") < 0)
        {
            CarBehaviourScript.carSpeed -= 0.01f;
            if (CarBehaviourScript.carSpeed < 0)
            {
                CarBehaviourScript.carSpeed = 0;
            }
        }

        Vector3 move = new Vector3(0, 0, - 1);
        transform.position += move * RoadSpeed * Time.deltaTime;


    }
}
