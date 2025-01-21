
forAll(fluidRegions,i)
{
    fvMesh& mesh = fluidRegions[i];
    const polyPatchList& patches = mesh.boundaryMesh();

    forAll (patches, patchI)
    {
        if (isType<regionCouplePolyPatch>(patches[patchI]))
        {
            monolithicEnergy = true;
        }
    }

}
